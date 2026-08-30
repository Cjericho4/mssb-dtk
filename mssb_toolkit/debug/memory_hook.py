"""Live GameCube RAM Hook with Multi-Backend Memory Engine.

Supports:
- ProcMemBackend: Direct Linux /proc/<pid>/mem access using os.pread / os.pwrite.
- SharedMemBackend: POSIX shared memory /dev/shm backend.
- GDBMemoryBackend: Memory bridge using Dolphin GDB RSP client.
- DolphinMemoryEngineBackend: dolphin_memory_engine C-extension wrapper.
- MockMemoryBackend: 24MB in-memory bytearray for unit tests and simulation.
- GameCubeMemoryHook: Unified accessor with address translation and big-endian primitives.
"""

from __future__ import annotations

import mmap
import os
import re
import struct
import subprocess
from abc import ABC, abstractmethod
from pathlib import Path
from typing import Any, List, Optional, Tuple, Union


class InvalidGameCubeAddressError(ValueError):
    """Raised when an address falls outside GameCube MEM1 bounds."""
    pass


class MemoryHookConnectionError(RuntimeError):
    """Raised when memory backend connection fails."""
    pass


class MemoryBackend(ABC):
    """Abstract base class for GameCube memory backends."""

    @abstractmethod
    def read_bytes(self, physical_offset: int, size: int) -> bytes:
        """Read size bytes starting at physical MEM1 offset (0..0x1800000)."""
        pass

    @abstractmethod
    def write_bytes(self, physical_offset: int, data: bytes) -> None:
        """Write bytes starting at physical MEM1 offset."""
        pass

    @abstractmethod
    def is_connected(self) -> bool:
        """Return True if backend connection is active."""
        pass

    def close(self) -> None:
        """Close backend handles."""
        pass


class MockMemoryBackend(MemoryBackend):
    """24MB in-memory bytearray for unit tests and simulation."""

    def __init__(self, size: int = 0x1800000):
        self.size = size
        self.buffer = bytearray(size)
        # Initialize standard GameCube boot header
        self.buffer[0x00:0x06] = b"GYQE01"
        struct.pack_into(">I", self.buffer, 0x1C, 0xC2339F3D)
        title = b"Mario Superstar Baseball"
        self.buffer[0x20 : 0x20 + len(title)] = title
        self._connected = True

    def read_bytes(self, physical_offset: int, size: int) -> bytes:
        if physical_offset < 0 or physical_offset + size > self.size:
            raise InvalidGameCubeAddressError(
                f"Offset 0x{physical_offset:08X} + {size} exceeds 24MB MEM1 bounds"
            )
        return bytes(self.buffer[physical_offset : physical_offset + size])

    def write_bytes(self, physical_offset: int, data: bytes) -> None:
        if physical_offset < 0 or physical_offset + len(data) > self.size:
            raise InvalidGameCubeAddressError(
                f"Offset 0x{physical_offset:08X} + {len(data)} exceeds 24MB MEM1 bounds"
            )
        self.buffer[physical_offset : physical_offset + len(data)] = data

    def is_connected(self) -> bool:
        return self._connected

    def close(self) -> None:
        self._connected = False


class ProcMemBackend(MemoryBackend):
    """Direct Linux /proc/<pid>/mem backend using os.pread / os.pwrite."""

    MEM1_SIZE = 0x1800000  # 24 MB

    def __init__(self, pid: int, mem1_vaddr: int):
        self.pid = pid
        self.mem1_vaddr = mem1_vaddr
        self.mem_path = f"/proc/{pid}/mem"
        try:
            self.fd = os.open(self.mem_path, os.O_RDWR | getattr(os, "O_LARGEFILE", 0))
        except PermissionError as e:
            raise MemoryHookConnectionError(
                f"Permission denied opening {self.mem_path}. Ensure same UID or CAP_SYS_PTRACE: {e}"
            )
        except OSError as e:
            raise MemoryHookConnectionError(f"Failed to open {self.mem_path}: {e}")
        self._connected = True

    @classmethod
    def discover_dolphin_mem1(cls, pid: Optional[int] = None) -> Tuple[int, int]:
        """Discover Dolphin process PID and MEM1 virtual address."""
        if pid is None:
            pid = cls.find_dolphin_pid()
            if pid is None:
                raise MemoryHookConnectionError("No running Dolphin process found")

        maps_path = f"/proc/{pid}/maps"
        if not os.path.exists(maps_path):
            raise MemoryHookConnectionError(f"Process {pid} does not exist or has no maps")

        # Parse maps for 24MB (0x1800000) or 32MB (0x2000000) mapping with rw-p / rw-s / rwxp
        candidates: List[int] = []
        with open(maps_path, "r") as f:
            for line in f:
                parts = line.strip().split()
                if len(parts) < 2:
                    continue
                addr_range, perms = parts[0], parts[1]
                if "rw" not in perms:
                    continue
                start_hex, end_hex = addr_range.split("-")
                start_vaddr = int(start_hex, 16)
                end_vaddr = int(end_hex, 16)
                span = end_vaddr - start_vaddr

                if span in (0x1800000, 0x2000000, 0x4000000):
                    candidates.append(start_vaddr)

        # Verify candidate by checking GYQE01 magic at offset 0
        mem_path = f"/proc/{pid}/mem"
        try:
            fd = os.open(mem_path, os.O_RDONLY | getattr(os, "O_LARGEFILE", 0))
            try:
                for vaddr in candidates:
                    try:
                        header = os.pread(fd, 6, vaddr)
                        if header == b"GYQE01":
                            return pid, vaddr
                    except OSError:
                        continue
            finally:
                os.close(fd)
        except Exception:
            pass

        if candidates:
            # Fall back to first candidate if magic not yet loaded (e.g. boot phase)
            return pid, candidates[0]

        raise MemoryHookConnectionError(
            f"Could not locate 24MB GameCube MEM1 mapping in Dolphin process {pid}"
        )

    @classmethod
    def find_dolphin_pid(cls) -> Optional[int]:
        """Find running Dolphin process ID."""
        for proc_name in [
            "dolphin-emu",
            "dolphin-emu-nogui",
            "dolphin-emu-nog",
            "dolphin-emu-qt2",
            "dolphin-emu-qt",
        ]:
            try:
                out = subprocess.check_output(["pgrep", "-f", proc_name], stderr=subprocess.DEVNULL)
                pids = [int(p.strip()) for p in out.decode().splitlines() if p.strip().isdigit()]
                if pids:
                    return pids[0]
            except Exception:
                continue
        return None

    def read_bytes(self, physical_offset: int, size: int) -> bytes:
        if not self._connected:
            raise MemoryHookConnectionError("Backend is closed")
        try:
            return os.pread(self.fd, size, self.mem1_vaddr + physical_offset)
        except OSError as e:
            raise RuntimeError(
                f"os.pread failed at vaddr 0x{self.mem1_vaddr + physical_offset:X}: {e}"
            )

    def write_bytes(self, physical_offset: int, data: bytes) -> None:
        if not self._connected:
            raise MemoryHookConnectionError("Backend is closed")
        try:
            os.pwrite(self.fd, data, self.mem1_vaddr + physical_offset)
        except OSError as e:
            raise RuntimeError(
                f"os.pwrite failed at vaddr 0x{self.mem1_vaddr + physical_offset:X}: {e}"
            )

    def is_connected(self) -> bool:
        return self._connected

    def close(self) -> None:
        if self._connected:
            try:
                os.close(self.fd)
            except Exception:
                pass
            self._connected = False


class SharedMemBackend(MemoryBackend):
    """POSIX shared memory /dev/shm backend."""

    def __init__(self, shm_path: Union[str, Path]):
        self.shm_path = Path(shm_path)
        if not self.shm_path.exists():
            raise MemoryHookConnectionError(f"Shared memory file {shm_path} does not exist")
        self.f = open(self.shm_path, "r+b")
        self.mmap_obj = mmap.mmap(self.f.fileno(), 0x1800000)
        self._connected = True

    def read_bytes(self, physical_offset: int, size: int) -> bytes:
        if physical_offset < 0 or physical_offset + size > 0x1800000:
            raise InvalidGameCubeAddressError("Out of bounds MEM1 offset")
        return self.mmap_obj[physical_offset : physical_offset + size]

    def write_bytes(self, physical_offset: int, data: bytes) -> None:
        if physical_offset < 0 or physical_offset + len(data) > 0x1800000:
            raise InvalidGameCubeAddressError("Out of bounds MEM1 offset")
        self.mmap_obj[physical_offset : physical_offset + len(data)] = data

    def is_connected(self) -> bool:
        return self._connected

    def close(self) -> None:
        if self._connected:
            self.mmap_obj.close()
            self.f.close()
            self._connected = False


class GDBMemoryBackend(MemoryBackend):
    """Memory backend routing memory operations over GDB RSP protocol."""

    def __init__(self, gdb_client: Any):
        self.client = gdb_client

    def read_bytes(self, physical_offset: int, size: int) -> bytes:
        gc_addr = 0x80000000 + physical_offset
        return self.client.read_memory(gc_addr, size)

    def write_bytes(self, physical_offset: int, data: bytes) -> None:
        gc_addr = 0x80000000 + physical_offset
        self.client.write_memory(gc_addr, data)

    def is_connected(self) -> bool:
        return self.client.is_connected()


class DolphinMemoryEngineBackend(MemoryBackend):
    """Wrapper backend for dolphin_memory_engine (dme) Python package."""

    def __init__(self) -> None:
        try:
            import dolphin_memory_engine as dme
            self.dme = dme
        except ImportError:
            raise MemoryHookConnectionError("dolphin_memory_engine package is not installed")

        if not self.dme.is_hooked():
            # Set process name hint on Linux
            os.environ.setdefault("DME_DOLPHIN_PROCESS_NAME", "dolphin-emu-nog")
            self.dme.hook()
            if not self.dme.is_hooked():
                raise MemoryHookConnectionError("Failed to hook dolphin_memory_engine to Dolphin")

    def read_bytes(self, physical_offset: int, size: int) -> bytes:
        addr = 0x80000000 + physical_offset
        return self.dme.read_bytes(addr, size)

    def write_bytes(self, physical_offset: int, data: bytes) -> None:
        addr = 0x80000000 + physical_offset
        self.dme.write_bytes(addr, data)

    def is_connected(self) -> bool:
        return self.dme.is_hooked()

    def close(self) -> None:
        if self.dme.is_hooked():
            self.dme.un_hook()


class GameCubeMemoryHook:
    """Unified GameCube MEM1 memory accessor with address translation and primitive I/O."""

    MEM1_SIZE = 0x01800000  # 24 MB (25,165,824 bytes)

    def __init__(self, backend: MemoryBackend):
        self.backend = backend

    @classmethod
    def from_mock(cls, size: int = 0x1800000) -> "GameCubeMemoryHook":
        """Create hook backed by 24MB in-memory MockMemoryBackend."""
        return cls(MockMemoryBackend(size=size))

    @classmethod
    def from_proc(cls, pid: Optional[int] = None) -> "GameCubeMemoryHook":
        """Create hook backed by Linux /proc/<pid>/mem."""
        found_pid, vaddr = ProcMemBackend.discover_dolphin_mem1(pid=pid)
        backend = ProcMemBackend(pid=found_pid, mem1_vaddr=vaddr)
        return cls(backend)

    @classmethod
    def from_shm(cls, path: Union[str, Path]) -> "GameCubeMemoryHook":
        """Create hook backed by POSIX shared memory /dev/shm."""
        return cls(SharedMemBackend(path))

    @classmethod
    def from_gdb(cls, client: Any) -> "GameCubeMemoryHook":
        """Create hook backed by GDB client."""
        return cls(GDBMemoryBackend(client))

    @classmethod
    def from_dme(cls) -> "GameCubeMemoryHook":
        """Create hook backed by dolphin_memory_engine."""
        return cls(DolphinMemoryEngineBackend())

    @classmethod
    def attach_dolphin(
        cls,
        preferred_backend: str = "auto",
        pid: Optional[int] = None,
        gdb_client: Optional[Any] = None,
    ) -> "GameCubeMemoryHook":
        """Auto-attach to running Dolphin emulator using best available backend."""
        if preferred_backend == "mock":
            return cls.from_mock()

        if preferred_backend == "gdb" and gdb_client:
            return cls.from_gdb(gdb_client)

        if preferred_backend in ("dme", "auto"):
            try:
                return cls.from_dme()
            except Exception:
                if preferred_backend == "dme":
                    raise

        if preferred_backend in ("proc", "auto"):
            try:
                return cls.from_proc(pid=pid)
            except Exception:
                if preferred_backend == "proc":
                    raise

        # Check for shm files in /dev/shm
        shm_candidates = list(Path("/dev/shm").glob("dolphin-emu*"))
        if shm_candidates:
            try:
                return cls.from_shm(shm_candidates[0])
            except Exception:
                pass

        if gdb_client:
            return cls.from_gdb(gdb_client)

        raise MemoryHookConnectionError("Failed to attach to Dolphin via any available backend")

    def translate_address(self, gc_addr: int) -> int:
        """Translate GameCube effective/uncached address to physical MEM1 offset (0..0x1800000)."""
        if 0x80000000 <= gc_addr < 0x81800000:
            return gc_addr - 0x80000000
        if 0xC0000000 <= gc_addr < 0xC1800000:
            return gc_addr - 0xC0000000
        if 0x00000000 <= gc_addr < 0x01800000:
            return gc_addr
        raise InvalidGameCubeAddressError(
            f"Address 0x{gc_addr:08X} outside GameCube MEM1 bounds (0x80000000..0x81800000)"
        )

    def is_connected(self) -> bool:
        return self.backend.is_connected()

    def close(self) -> None:
        self.backend.close()

    # --- Primitive Big-Endian Memory Accessors ---

    def read_bytes(self, addr: int, size: int) -> bytes:
        offset = self.translate_address(addr)
        return self.backend.read_bytes(offset, size)

    def write_bytes(self, addr: int, data: bytes) -> None:
        offset = self.translate_address(addr)
        self.backend.write_bytes(offset, data)

    def read_u8(self, addr: int) -> int:
        return self.read_bytes(addr, 1)[0]

    def read_u16(self, addr: int) -> int:
        data = self.read_bytes(addr, 2)
        return struct.unpack(">H", data)[0]

    def read_u32(self, addr: int) -> int:
        data = self.read_bytes(addr, 4)
        return struct.unpack(">I", data)[0]

    def read_u64(self, addr: int) -> int:
        data = self.read_bytes(addr, 8)
        return struct.unpack(">Q", data)[0]

    def read_s8(self, addr: int) -> int:
        data = self.read_bytes(addr, 1)
        return struct.unpack(">b", data)[0]

    def read_s16(self, addr: int) -> int:
        data = self.read_bytes(addr, 2)
        return struct.unpack(">h", data)[0]

    def read_s32(self, addr: int) -> int:
        data = self.read_bytes(addr, 4)
        return struct.unpack(">i", data)[0]

    def read_f32(self, addr: int) -> float:
        data = self.read_bytes(addr, 4)
        return struct.unpack(">f", data)[0]

    def read_f64(self, addr: int) -> float:
        data = self.read_bytes(addr, 8)
        return struct.unpack(">d", data)[0]

    def read_string(self, addr: int, max_len: int = 256, encoding: str = "utf-8") -> str:
        """Read null-terminated ASCII/UTF-8 string from memory."""
        raw = self.read_bytes(addr, max_len)
        null_idx = raw.find(b"\x00")
        if null_idx != -1:
            raw = raw[:null_idx]
        return raw.decode(encoding, errors="replace")

    def write_u8(self, addr: int, val: int) -> None:
        self.write_bytes(addr, bytes([val & 0xFF]))

    def write_u16(self, addr: int, val: int) -> None:
        self.write_bytes(addr, struct.pack(">H", val & 0xFFFF))

    def write_u32(self, addr: int, val: int) -> None:
        self.write_bytes(addr, struct.pack(">I", val & 0xFFFFFFFF))

    def write_u64(self, addr: int, val: int) -> None:
        self.write_bytes(addr, struct.pack(">Q", val & 0xFFFFFFFFFFFFFFFF))

    def write_f32(self, addr: int, val: float) -> None:
        self.write_bytes(addr, struct.pack(">f", float(val)))

    def write_string(
        self,
        addr: int,
        s: str,
        encoding: str = "utf-8",
        null_terminate: bool = True,
    ) -> None:
        data = s.encode(encoding)
        if null_terminate:
            data += b"\x00"
        self.write_bytes(addr, data)
