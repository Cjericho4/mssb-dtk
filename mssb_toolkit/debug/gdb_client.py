"""Pure-Python Dolphin GDB Remote Serial Protocol (RSP) Debugger Bridge.

Provides:
- GDBRemoteProtocol: Pure-Python socket implementation of the GDB RSP protocol.
- PowerPCRegisters: PowerPC 750/Gekko register set decoding (32 GPRs, 32 FPRs, SPRs).
- PPCStackUnwinder & StackFrame: PowerPC 32-bit EABI backtrace unwinding via 0(r1) and 4(*r1).
- DolphinGDBClient: High-level debugging client with automated crash trap interception.
- MockGDBServer: In-memory multi-threaded GDB RSP server for deterministic testing.
"""

from __future__ import annotations

import os
import socket
import struct
import threading
import time
from dataclasses import dataclass, field
from typing import Callable, Dict, List, Optional, Tuple, Union


class GDBRemoteProtocol:
    """Low-level GDB Remote Serial Protocol (RSP) socket client."""

    def __init__(self, host: str = "127.0.0.1", port: int = 2828, timeout: float = 5.0):
        self.host = host
        self.port = port
        self.timeout = timeout
        self.sock: Optional[socket.socket] = None
        self._lock = threading.Lock()

    def connect(self, retry_count: int = 15, retry_delay: float = 0.3) -> None:
        """Connect to GDB server with retry backoff."""
        with self._lock:
            last_err = None
            for attempt in range(retry_count):
                try:
                    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    s.settimeout(self.timeout)
                    s.connect((self.host, self.port))
                    self.sock = s
                    return
                except (ConnectionRefusedError, socket.timeout, OSError) as e:
                    last_err = e
                    time.sleep(retry_delay)
            raise ConnectionError(
                f"Failed to connect to GDB server at {self.host}:{self.port} after {retry_count} attempts: {last_err}"
            )

    def disconnect(self) -> None:
        """Disconnect from GDB server."""
        with self._lock:
            if self.sock:
                try:
                    self.send_packet_locked("D")
                except Exception:
                    pass
                try:
                    self.sock.close()
                except Exception:
                    pass
                self.sock = None

    def is_connected(self) -> bool:
        return self.sock is not None

    @staticmethod
    def calculate_checksum(data: str) -> str:
        """Compute 2-character hex checksum: sum(ord(c)) % 256."""
        chk = sum(data.encode("ascii", errors="replace")) % 256
        return f"{chk:02x}"

    def send_packet_locked(self, payload: str, max_retries: int = 3) -> None:
        """Send an RSP packet `$payload#checksum` and await `+` ACK."""
        if not self.sock:
            raise ConnectionError("Not connected to GDB server")

        chk = self.calculate_checksum(payload)
        packet = f"${payload}#{chk}".encode("ascii")

        for _ in range(max_retries):
            self.sock.sendall(packet)
            # Read single-byte ACK
            ack = self.sock.recv(1)
            if ack == b"+":
                return
            elif ack == b"-":
                continue  # Resend packet on NACK
            elif ack == b"$":
                # Some stubs might respond immediately with packet
                # Put byte back if possible or handle
                return
        raise RuntimeError(f"GDB server failed to ACK packet: ${payload}#{chk}")

    def recv_packet_locked(self) -> str:
        """Receive an RSP packet `$payload#checksum` and return payload."""
        if not self.sock:
            raise ConnectionError("Not connected to GDB server")

        # Read until '$'
        buf = bytearray()
        while True:
            b = self.sock.recv(1)
            if not b:
                raise ConnectionError("GDB socket closed unexpectedly")
            if b == b"$":
                break
            # Skip ACK/NACK or notification characters

        # Read payload until '#'
        payload_bytes = bytearray()
        while True:
            b = self.sock.recv(1)
            if not b:
                raise ConnectionError("GDB socket closed while reading payload")
            if b == b"#":
                break
            payload_bytes.append(b[0])

        # Read 2-char checksum
        chk_bytes = self.sock.recv(2)
        if len(chk_bytes) < 2:
            raise ConnectionError("GDB socket closed while reading checksum")

        payload_str = payload_bytes.decode("ascii", errors="replace")
        expected_chk = self.calculate_checksum(payload_str)
        recv_chk = chk_bytes.decode("ascii", errors="replace").lower()

        if recv_chk != expected_chk.lower():
            # Send NACK
            self.sock.sendall(b"-")
            raise ValueError(f"Checksum mismatch: received {recv_chk}, calculated {expected_chk} for {payload_str}")

        # Send ACK
        self.sock.sendall(b"+")
        return payload_str

    def send_command(self, payload: str) -> str:
        """Thread-safe command execution: send packet and receive response."""
        with self._lock:
            self.send_packet_locked(payload)
            return self.recv_packet_locked()

    def interrupt(self) -> str:
        """Send raw 0x03 byte (SIGINT / Break) and return stop response."""
        with self._lock:
            if not self.sock:
                raise ConnectionError("Not connected")
            self.sock.sendall(b"\x03")
            return self.recv_packet_locked()


@dataclass
class PowerPCRegisters:
    """Decoded PowerPC 750 / Gekko CPU register set."""

    gprs: List[int] = field(default_factory=lambda: [0] * 32)
    fprs: List[float] = field(default_factory=lambda: [0.0] * 32)
    pc: int = 0
    msr: int = 0
    cr: int = 0
    lr: int = 0
    ctr: int = 0
    xer: int = 0
    fpscr: int = 0

    @property
    def r0(self) -> int: return self.gprs[0]
    @property
    def r1(self) -> int: return self.gprs[1]  # Stack Pointer (SP)
    @property
    def r2(self) -> int: return self.gprs[2]  # TOC / SDA2
    @property
    def r3(self) -> int: return self.gprs[3]
    @property
    def r4(self) -> int: return self.gprs[4]
    @property
    def r5(self) -> int: return self.gprs[5]
    @property
    def r6(self) -> int: return self.gprs[6]
    @property
    def r13(self) -> int: return self.gprs[13]  # SDA1
    @property
    def r30(self) -> int: return self.gprs[30]
    @property
    def r31(self) -> int: return self.gprs[31]

    def __getitem__(self, item: Union[int, str]) -> int:
        if isinstance(item, int):
            return self.gprs[item]
        item_lower = item.lower()
        if item_lower.startswith("r") and item_lower[1:].isdigit():
            idx = int(item_lower[1:])
            if 0 <= idx < 32:
                return self.gprs[idx]
        if hasattr(self, item_lower):
            val = getattr(self, item_lower)
            if isinstance(val, int):
                return val
        raise KeyError(f"Unknown PowerPC register: {item}")

    @classmethod
    def from_g_packet(cls, hex_data: str) -> "PowerPCRegisters":
        """Parse register dump from standard GDB $g packet hex string.
        
        Layout (PowerPC 32-bit big-endian):
        - 32 GPRs: 32 * 4 bytes = 128 bytes = 256 hex chars
        - 32 FPRs: 32 * 8 bytes = 256 bytes = 512 hex chars
        - SPRs:
          - PC: 4 bytes (8 hex chars)
          - MSR: 4 bytes (8 hex chars)
          - CR: 4 bytes (8 hex chars)
          - LR: 4 bytes (8 hex chars)
          - CTR: 4 bytes (8 hex chars)
          - XER: 4 bytes (8 hex chars)
          - FPSCR: 4 bytes (8 hex chars)
        Total standard length: 824 hex chars.
        """
        raw = bytes.fromhex(hex_data)
        regs = cls()

        # Parse 32 GPRs (4 bytes each)
        if len(raw) >= 128:
            for i in range(32):
                regs.gprs[i] = struct.unpack_from(">I", raw, i * 4)[0]

        # Parse 32 FPRs (8 bytes each)
        if len(raw) >= 128 + 256:
            for i in range(32):
                regs.fprs[i] = struct.unpack_from(">d", raw, 128 + i * 8)[0]

        # Parse SPRs
        spr_offset = 128 + 256
        if len(raw) >= spr_offset + 4:
            regs.pc = struct.unpack_from(">I", raw, spr_offset)[0]
        if len(raw) >= spr_offset + 8:
            regs.msr = struct.unpack_from(">I", raw, spr_offset + 4)[0]
        if len(raw) >= spr_offset + 12:
            regs.cr = struct.unpack_from(">I", raw, spr_offset + 8)[0]
        if len(raw) >= spr_offset + 16:
            regs.lr = struct.unpack_from(">I", raw, spr_offset + 12)[0]
        if len(raw) >= spr_offset + 20:
            regs.ctr = struct.unpack_from(">I", raw, spr_offset + 16)[0]
        if len(raw) >= spr_offset + 24:
            regs.xer = struct.unpack_from(">I", raw, spr_offset + 20)[0]
        if len(raw) >= spr_offset + 28:
            regs.fpscr = struct.unpack_from(">I", raw, spr_offset + 24)[0]

        return regs

    def to_g_packet(self) -> str:
        """Encode registers to GDB $g packet hex string (824 characters)."""
        buf = bytearray(128 + 256 + 28)
        # 32 GPRs
        for i in range(32):
            struct.pack_into(">I", buf, i * 4, self.gprs[i] & 0xFFFFFFFF)
        # 32 FPRs
        for i in range(32):
            struct.pack_into(">d", buf, 128 + i * 8, float(self.fprs[i]))
        # SPRs
        spr_offset = 128 + 256
        struct.pack_into(">I", buf, spr_offset + 0, self.pc & 0xFFFFFFFF)
        struct.pack_into(">I", buf, spr_offset + 4, self.msr & 0xFFFFFFFF)
        struct.pack_into(">I", buf, spr_offset + 8, self.cr & 0xFFFFFFFF)
        struct.pack_into(">I", buf, spr_offset + 12, self.lr & 0xFFFFFFFF)
        struct.pack_into(">I", buf, spr_offset + 16, self.ctr & 0xFFFFFFFF)
        struct.pack_into(">I", buf, spr_offset + 20, self.xer & 0xFFFFFFFF)
        struct.pack_into(">I", buf, spr_offset + 24, self.fpscr & 0xFFFFFFFF)
        return buf.hex()

    def format_table(self) -> str:
        """Format registers as clean human-readable table."""
        lines = ["=== PowerPC 750 / Gekko Registers ==="]
        for i in range(0, 32, 4):
            line = (
                f"r{i:02d}: 0x{self.gprs[i]:08X}   "
                f"r{i+1:02d}: 0x{self.gprs[i+1]:08X}   "
                f"r{i+2:02d}: 0x{self.gprs[i+2]:08X}   "
                f"r{i+3:02d}: 0x{self.gprs[i+3]:08X}"
            )
            lines.append(line)
        lines.append("--- Special Purpose Registers ---")
        lines.append(
            f"PC : 0x{self.pc:08X}   LR : 0x{self.lr:08X}   "
            f"CTR: 0x{self.ctr:08X}   MSR: 0x{self.msr:08X}"
        )
        lines.append(
            f"CR : 0x{self.cr:08X}   XER: 0x{self.xer:08X}   "
            f"FPSCR: 0x{self.fpscr:08X}"
        )
        return "\n".join(lines)

    def to_dict(self) -> Dict[str, Union[int, float]]:
        """Return dict representation of all registers."""
        res: Dict[str, Union[int, float]] = {f"r{i}": self.gprs[i] for i in range(32)}
        for i in range(32):
            res[f"f{i}"] = self.fprs[i]
        res["pc"] = self.pc
        res["msr"] = self.msr
        res["cr"] = self.cr
        res["lr"] = self.lr
        res["ctr"] = self.ctr
        res["xer"] = self.xer
        res["fpscr"] = self.fpscr
        return res


@dataclass
class StackFrame:
    """Represents a single PowerPC callstack frame."""

    level: int
    pc: int
    sp: int
    lr: int
    symbol: Optional[str] = None

    def __str__(self) -> str:
        sym_str = f" in {self.symbol}" if self.symbol else ""
        return f"#{self.level:02d}  0x{self.pc:08X}{sym_str} (SP: 0x{self.sp:08X}, LR: 0x{self.lr:08X})"


class PPCStackUnwinder:
    """PowerPC 32-bit EABI back-chain callstack unwinder.
    
    In PowerPC 32-bit EABI:
    - 0(r1) stores the back-chain pointer (caller SP)
    - 4(*r1) stores the saved Link Register (return address into caller)
    """

    @classmethod
    def unwind(
        cls,
        regs: PowerPCRegisters,
        read_u32_fn: Callable[[int], int],
        symbol_lookup_fn: Optional[Callable[[int], Optional[str]]] = None,
        max_depth: int = 32,
    ) -> List[StackFrame]:
        frames: List[StackFrame] = []

        # Frame 0: Current execution state
        sp = regs.gprs[1]  # r1
        pc = regs.pc
        lr = regs.lr
        sym0 = symbol_lookup_fn(pc) if symbol_lookup_fn else None
        frames.append(StackFrame(level=0, pc=pc, sp=sp, lr=lr, symbol=sym0))

        # Check stack pointer validity
        if sp == 0 or (sp & 3) != 0 or not (0x80000000 <= sp < 0x81800000):
            return frames

        curr_sp = sp
        for depth in range(1, max_depth):
            try:
                # 0(curr_sp) = back-chain pointer
                prev_sp = read_u32_fn(curr_sp)
            except Exception:
                break

            # Terminate on NULL, unaligned, out-of-bounds, or circular/non-growing stack
            if prev_sp == 0:
                break
            if (prev_sp & 3) != 0:
                break
            if not (0x80000000 <= prev_sp < 0x81800000):
                break
            if prev_sp <= curr_sp:
                # In PowerPC stack grows downward, so caller SP must be greater than callee SP
                break

            try:
                # 4(prev_sp) = saved return address (LR)
                ret_pc = read_u32_fn(prev_sp + 4)
            except Exception:
                break

            if ret_pc == 0:
                break

            sym = symbol_lookup_fn(ret_pc) if symbol_lookup_fn else None
            frames.append(StackFrame(level=depth, pc=ret_pc, sp=prev_sp, lr=ret_pc, symbol=sym))
            curr_sp = prev_sp

        return frames


@dataclass
class CrashContext:
    """Diagnostic crash snapshot when CPU halts on breakpoint or exception."""

    pc: int
    stop_signal: int
    registers: PowerPCRegisters
    backtrace: List[StackFrame]
    memory_dumps: Dict[str, str]  # "r3", "r6", "r30", "r31" -> formatted hex dumps
    error_classification: str

    def format_markdown_report(self) -> str:
        """Produce structured Markdown diagnostic report."""
        lines = [
            "# GameCube Crash Diagnostic Report",
            "",
            f"**Halt Program Counter (PC):** `0x{self.pc:08X}`  ",
            f"**Stop Signal:** `Signal {self.stop_signal}`  ",
            f"**Classification:** {self.error_classification}  ",
            "",
            "## Call Stack Backtrace",
            "```",
        ]
        for f in self.backtrace:
            lines.append(str(f))
        lines.extend([
            "```",
            "",
            "## PowerPC CPU Registers",
            "```",
            self.registers.format_table(),
            "```",
            "",
            "## Base Register Memory Dumps (±0x20 bytes)",
        ])
        for reg_name, dump in self.memory_dumps.items():
            lines.extend([
                f"### Register {reg_name} (0x{self.registers[reg_name]:08X})",
                "```",
                dump,
                "```",
                "",
            ])
        return "\n".join(lines)


class DolphinGDBClient:
    """High-level GDB debugging bridge for Dolphin emulator."""

    KNOWN_CRASH_PCS: Dict[int, str] = {
        0x8063F148: "Error 8: game.rel INIT_EVENT NULL Pointer Write (stw r0, 0(r31))",
        0x800233A0: "Error 4: f_InitActorWithLayout Glove Bone Attachment NULL Dereference (lwz r3, 0xC(r31))",
        0x800C07AC: "Error 3/5/7: convertTextureHeader Double-Relocation / Truncated Model Read (lwz r0, 4(r6))",
        0x800B4FC0: "Error 2: ANIMGetTrackFromSequence Skeletal Dereference Fault (lwz r0, 0x0A(r3))",
        0x800B4910: "Error 6: LoadActorLayout Compressed Stream Bypass (r3 = compressed header)",
        0x80017814: "Error 1: LoadModel Bone Count Mismatch Panic",
        0x800A6654: "Error 0: DecompressDiskData Lookback Underflow Panic",
    }

    def __init__(self, host: str = "127.0.0.1", port: int = 2828, timeout: float = 5.0):
        self.proto = GDBRemoteProtocol(host=host, port=port, timeout=timeout)
        self.active_breakpoints: set[int] = set()

    def connect(self, retry_count: int = 15, retry_delay: float = 0.3) -> None:
        """Connect to Dolphin GDB stub."""
        self.proto.connect(retry_count=retry_count, retry_delay=retry_delay)
        # Query halt status / qSupported
        try:
            self.proto.send_command("qSupported:multiprocess+;swbreak+;hwbreak+")
        except Exception:
            pass

    def disconnect(self) -> None:
        """Disconnect and resume CPU if possible."""
        self.proto.disconnect()

    def is_connected(self) -> bool:
        return self.proto.is_connected()

    def set_breakpoint(self, address: int) -> bool:
        """Set software breakpoint Z0 at GameCube instruction address."""
        addr_hex = f"{address:08x}"
        resp = self.proto.send_command(f"Z0,{addr_hex},4")
        if resp == "OK":
            self.active_breakpoints.add(address)
            return True
        return False

    def clear_breakpoint(self, address: int) -> bool:
        """Clear software breakpoint z0."""
        addr_hex = f"{address:08x}"
        resp = self.proto.send_command(f"z0,{addr_hex},4")
        if resp == "OK":
            self.active_breakpoints.discard(address)
            return True
        return False

    def arm_known_crash_traps(self) -> Dict[int, bool]:
        """Arm breakpoints on all 7 known vulnerability crash PCs."""
        results = {}
        for addr, desc in self.KNOWN_CRASH_PCS.items():
            ok = self.set_breakpoint(addr)
            results[addr] = ok
        return results

    def read_memory(self, address: int, length: int) -> bytes:
        """Read memory via m<addr_hex>,<len_hex>."""
        addr_hex = f"{address:08x}"
        len_hex = f"{length:x}"
        resp = self.proto.send_command(f"m{addr_hex},{len_hex}")
        if resp.startswith("E") or len(resp) != length * 2:
            raise RuntimeError(f"Failed to read {length} bytes from 0x{address:08X}: {resp}")
        return bytes.fromhex(resp)

    def write_memory(self, address: int, data: bytes) -> bool:
        """Write memory via M<addr_hex>,<len_hex>:<data_hex>."""
        addr_hex = f"{address:08x}"
        len_hex = f"{len(data):x}"
        data_hex = data.hex()
        resp = self.proto.send_command(f"M{addr_hex},{len_hex}:{data_hex}")
        return resp == "OK"

    def read_u32(self, address: int) -> int:
        """Read 32-bit big-endian integer from GameCube memory."""
        data = self.read_memory(address, 4)
        return struct.unpack(">I", data)[0]

    def write_u32(self, address: int, value: int) -> bool:
        """Write 32-bit big-endian integer to GameCube memory."""
        data = struct.pack(">I", value & 0xFFFFFFFF)
        return self.write_memory(address, data)

    def read_registers(self) -> PowerPCRegisters:
        """Read all CPU registers via $g command."""
        resp = self.proto.send_command("g")
        return PowerPCRegisters.from_g_packet(resp)

    def write_registers(self, regs: PowerPCRegisters) -> bool:
        """Write all CPU registers via $G command."""
        g_data = regs.to_g_packet()
        resp = self.proto.send_command(f"G{g_data}")
        return resp == "OK"

    def continue_execution(self) -> str:
        """Resume CPU execution ($c) and await next halt packet."""
        return self.proto.send_command("c")

    def single_step(self) -> str:
        """Single step one CPU instruction ($s)."""
        return self.proto.send_command("s")

    def pause(self) -> str:
        """Send interrupt (0x03) to pause running CPU."""
        return self.proto.interrupt()

    def dump_memory_around(self, address: int, radius: int = 0x20) -> str:
        """Dump formatted memory ±radius bytes around target address with NULL/OOB detection."""
        if address == 0:
            return "[NULL POINTER - 0x00000000]"
        if not (0x80000000 <= address < 0x81800000):
            return f"[OUT-OF-BOUNDS POINTER - 0x{address:08X}]"

        start_addr = max(0x80000000, (address - radius) & ~0xF)
        end_addr = min(0x81800000, (address + radius + 15) & ~0xF)
        length = end_addr - start_addr

        try:
            mem = self.read_memory(start_addr, length)
        except Exception as e:
            return f"[MEMORY READ ERROR at 0x{start_addr:08X}: {e}]"

        lines = []
        for offset in range(0, len(mem), 16):
            cur_addr = start_addr + offset
            chunk = mem[offset : offset + 16]
            hex_part = " ".join(f"{b:02X}" for b in chunk)
            ascii_part = "".join(chr(b) if 32 <= b < 127 else "." for b in chunk)
            marker = " ->" if cur_addr <= address < cur_addr + 16 else "   "
            lines.append(f"{marker} 0x{cur_addr:08X}:  {hex_part:<48}  |{ascii_part}|")

        return "\n".join(lines)

    def capture_crash_context(
        self,
        stop_signal: int = 5,
        symbol_lookup_fn: Optional[Callable[[int], Optional[str]]] = None,
    ) -> CrashContext:
        """Capture comprehensive diagnostic snapshot."""
        regs = self.read_registers()
        backtrace = PPCStackUnwinder.unwind(
            regs=regs,
            read_u32_fn=self.read_u32,
            symbol_lookup_fn=symbol_lookup_fn,
        )

        memory_dumps = {}
        for reg_name in ["r3", "r6", "r30", "r31"]:
            reg_val = regs[reg_name]
            memory_dumps[reg_name] = self.dump_memory_around(reg_val, radius=0x20)

        classification = self.KNOWN_CRASH_PCS.get(
            regs.pc,
            f"Unknown Halt / Breakpoint at 0x{regs.pc:08X}",
        )

        return CrashContext(
            pc=regs.pc,
            stop_signal=stop_signal,
            registers=regs,
            backtrace=backtrace,
            memory_dumps=memory_dumps,
            error_classification=classification,
        )


class MockGDBServer(threading.Thread):
    """In-memory TCP GDB server simulating Dolphin GDBStub for unit testing."""

    def __init__(self, host: str = "127.0.0.1", port: int = 0):
        super().__init__(daemon=True)
        self.host = host
        self.server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_sock.bind((self.host, port))
        self.port = self.server_sock.getsockname()[1]
        self.server_sock.listen(1)
        self.running = True

        self.regs = PowerPCRegisters()
        self.memory: bytearray = bytearray(0x1800000)  # 24 MB GameCube RAM
        self.breakpoints: set[int] = set()
        self.halt_reason: str = "S05"
        self._step_target_pc: Optional[int] = None
        self._trigger_bp_event = threading.Event()

    def set_mock_state(
        self,
        pc: int,
        regs: Optional[PowerPCRegisters] = None,
        memory_writes: Optional[Dict[int, bytes]] = None,
    ) -> None:
        """Set mock CPU and RAM state."""
        if regs:
            self.regs = regs
        self.regs.pc = pc
        if memory_writes:
            for addr, data in memory_writes.items():
                offset = addr - 0x80000000 if 0x80000000 <= addr < 0x81800000 else addr
                if 0 <= offset < len(self.memory):
                    self.memory[offset : offset + len(data)] = data

    def trigger_breakpoint(self, pc: int) -> None:
        """Simulate CPU hitting a breakpoint at given PC."""
        self.regs.pc = pc
        self.halt_reason = "S05"
        self._trigger_bp_event.set()

    def run(self) -> None:
        while self.running:
            try:
                self.server_sock.settimeout(0.5)
                client_sock, _ = self.server_sock.accept()
            except socket.timeout:
                continue
            except OSError:
                break

            client_sock.settimeout(1.0)
            self._handle_client(client_sock)

    def _handle_client(self, client_sock: socket.socket) -> None:
        try:
            while self.running:
                # Read packet
                buf = bytearray()
                while True:
                    b = client_sock.recv(1)
                    if not b:
                        return
                    if b == b"$":
                        break
                    if b == b"\x03":  # Interrupt
                        self._send_packet(client_sock, self.halt_reason)

                payload = bytearray()
                while True:
                    b = client_sock.recv(1)
                    if not b or b == b"#":
                        break
                    payload.append(b[0])

                chk = client_sock.recv(2)
                client_sock.sendall(b"+")  # ACK

                cmd = payload.decode("ascii", errors="replace")
                resp = self._process_command(cmd)
                if resp is not None:
                    self._send_packet(client_sock, resp)
                if cmd == "D":
                    break
        except Exception:
            pass
        finally:
            client_sock.close()

    def _send_packet(self, client_sock: socket.socket, payload: str) -> None:
        chk = GDBRemoteProtocol.calculate_checksum(payload)
        client_sock.sendall(f"${payload}#{chk}".encode("ascii"))

    def _process_command(self, cmd: str) -> Optional[str]:
        if cmd == "?":
            return self.halt_reason
        if cmd.startswith("qSupported"):
            return "PacketSize=4000;qXfer:memory-map:read-;swbreak+;hwbreak+"
        if cmd == "g":
            return self.regs.to_g_packet()
        if cmd.startswith("G"):
            hex_data = cmd[1:]
            self.regs = PowerPCRegisters.from_g_packet(hex_data)
            return "OK"
        if cmd.startswith("m"):
            # m<addr>,<len>
            parts = cmd[1:].split(",")
            addr = int(parts[0], 16)
            length = int(parts[1], 16)
            offset = addr - 0x80000000 if 0x80000000 <= addr < 0x81800000 else addr
            if 0 <= offset <= len(self.memory) - length:
                data = self.memory[offset : offset + length]
                return data.hex()
            return "E01"
        if cmd.startswith("M"):
            # M<addr>,<len>:<data>
            head, data_hex = cmd[1:].split(":")
            addr_str, len_str = head.split(",")
            addr = int(addr_str, 16)
            length = int(len_str, 16)
            data = bytes.fromhex(data_hex)
            offset = addr - 0x80000000 if 0x80000000 <= addr < 0x81800000 else addr
            if 0 <= offset <= len(self.memory) - length:
                self.memory[offset : offset + length] = data
                return "OK"
            return "E01"
        if cmd.startswith("Z0,"):
            # Z0,<addr>,4
            addr = int(cmd.split(",")[1], 16)
            self.breakpoints.add(addr)
            return "OK"
        if cmd.startswith("z0,"):
            addr = int(cmd.split(",")[1], 16)
            self.breakpoints.discard(addr)
            return "OK"
        if cmd == "c":
            # Continue
            return self.halt_reason
        if cmd == "s":
            # Step
            self.regs.pc += 4
            return self.halt_reason
        if cmd == "D":
            return "OK"
        return ""

    def stop(self) -> None:
        """Stop mock server and close socket."""
        self.running = False
        try:
            self.server_sock.close()
        except Exception:
            pass
