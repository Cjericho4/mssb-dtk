"""Model Container Pointer Relocation and Double-Relocation Auditor.

Audits GEOPalette and GEODescriptor structures in GameCube RAM to detect
and prevent the 0xebca805e double-relocation pointer overflow bug in
LoadGeoPalette (0x800BCB44) and convertTextureHeader (0x800C0770).
"""

from __future__ import annotations

import struct
from dataclasses import dataclass
from typing import Any, Dict, List, Optional, Tuple

from mssb_toolkit.debug.memory_hook import GameCubeMemoryHook


@dataclass
class PointerAuditResult:
    """Audit outcome for an individual pointer in a RAM model container."""

    offset_in_buffer: int
    gc_address: int
    pointer_value: int
    status: str  # "UNRELOCATED", "RELOCATED_ONCE", "DOUBLE_RELOCATED", "CORRUPTED", "NULL"
    description: str


class ModelRelocationAuditor:
    """Audits GameCube RAM model buffers to enforce single relocation and heap separation."""

    # Standard Donkey Kong / Character .gpc texture descriptor sub-offsets
    KNOWN_TEXTURE_OFFSETS = [
        0x002580,  # Primary 64x64 Fur
        0x002D80,  # Primary 128x128 Body
        0x019640,  # Aux 64x64 Fur
        0x01A1A0,  # Aux 32x32 Tie
        0x01A660,  # Aux 128x128 Body
        0x01D0E0,  # Mipmap 1
        0x01D100,  # Mipmap 2
        0x01D120,  # Mipmap 3
    ]

    @classmethod
    def classify_pointer(cls, val: int, base_addr: int = 0x80C80000) -> str:
        """Classify a 32-bit pointer read from RAM."""
        if val == 0:
            return "NULL"
        # Relative offset before relocation: small positive offset inside container
        if 0 < val < 0x00080000:
            return "UNRELOCATED"
        # Valid single relocation into GameCube MEM1: 0x80000000..0x81800000
        if 0x80000000 <= val < 0x81800000:
            return "RELOCATED_ONCE"
        # Double relocation overflow: pointer added to base twice (e.g. 0x80C80000 + 0x80C84DE0 = 0x101904DE0 -> 0xebca805e / 0x01904DE0)
        if val == 0xEBCA805E or (val & 0xFF000000) in (0xEB000000, 0x6C000000) or val >= 0x81800000:
            return "DOUBLE_RELOCATED"
        return "CORRUPTED"

    @classmethod
    def audit_model_buffer(
        cls,
        hook: GameCubeMemoryHook,
        model_ram_addr: int,
        texture_offsets: Optional[List[int]] = None,
        max_scan_size: int = 0x20000,
    ) -> List[PointerAuditResult]:
        """Audit pointer relocation status at key offsets within a RAM model buffer."""
        offsets_to_check = texture_offsets or cls.KNOWN_TEXTURE_OFFSETS
        results: List[PointerAuditResult] = []

        for off in offsets_to_check:
            gc_addr = model_ram_addr + off
            try:
                val = hook.read_u32(gc_addr)
            except Exception as e:
                results.append(
                    PointerAuditResult(
                        offset_in_buffer=off,
                        gc_address=gc_addr,
                        pointer_value=0,
                        status="CORRUPTED",
                        description=f"Memory read error at 0x{gc_addr:08X}: {e}",
                    )
                )
                continue

            status = cls.classify_pointer(val, base_addr=model_ram_addr)
            desc_map = {
                "NULL": "Null pointer",
                "UNRELOCATED": f"Raw relative offset (0x{val:06X}) awaiting LoadGeoPalette relocation",
                "RELOCATED_ONCE": f"Valid GameCube MEM1 pointer (0x{val:08X})",
                "DOUBLE_RELOCATED": f"CRITICAL BUG: Double-relocated pointer overflow (0x{val:08X})",
                "CORRUPTED": f"Corrupted pointer (0x{val:08X}) outside valid memory bounds",
            }
            results.append(
                PointerAuditResult(
                    offset_in_buffer=off,
                    gc_address=gc_addr,
                    pointer_value=val,
                    status=status,
                    description=desc_map.get(status, "Unknown pointer state"),
                )
            )

        return results

    @classmethod
    def audit_geopalette_structure(
        cls,
        hook: GameCubeMemoryHook,
        geopal_addr: int,
    ) -> Dict[str, Any]:
        """Parse GEOPalette layout struct at geopal_addr to verify relocation integrity."""
        # Read GEOPalette header: numDescriptors (u16), versionNumber (u16), descriptorArray offset/ptr (u32)
        try:
            num_desc = hook.read_u16(geopal_addr)
            version = hook.read_u16(geopal_addr + 2)
            desc_array_raw = hook.read_u32(geopal_addr + 4)
        except Exception as e:
            return {
                "is_safe": False,
                "error": f"Failed to read GEOPalette header at 0x{geopal_addr:08X}: {e}",
                "corrupted_pointers": [],
            }

        desc_status = cls.classify_pointer(desc_array_raw, base_addr=geopal_addr)
        corrupted: List[Dict[str, Any]] = []

        if desc_status in ("DOUBLE_RELOCATED", "CORRUPTED"):
            corrupted.append({
                "field": "descriptorArray",
                "addr": geopal_addr + 4,
                "value": desc_array_raw,
                "status": desc_status,
            })

        is_safe = (len(corrupted) == 0) and (desc_status in ("UNRELOCATED", "RELOCATED_ONCE"))

        return {
            "geopal_addr": hex(geopal_addr),
            "num_descriptors": num_desc,
            "version": version,
            "descriptor_array_ptr": hex(desc_array_raw),
            "descriptor_status": desc_status,
            "is_safe": is_safe,
            "corrupted_pointers": corrupted,
        }

    @classmethod
    def assert_heap_separation(
        cls,
        slot2_ptr: int,
        slot21_ptr: int,
        min_separation: int = 119736,
    ) -> Tuple[bool, int, str]:
        """Verify that Slot 2 (Donkey Kong) and Slot 21 (Secondary DK) occupy distinct, non-overlapping heap arenas."""
        if not (0x80000000 <= slot2_ptr < 0x81800000):
            return False, 0, f"Slot 2 model pointer (0x{slot2_ptr:08X}) is outside valid GameCube RAM"

        if not (0x80000000 <= slot21_ptr < 0x81800000):
            return False, 0, f"Slot 21 model pointer (0x{slot21_ptr:08X}) is outside valid GameCube RAM"

        delta = abs(slot2_ptr - slot21_ptr)
        if delta < min_separation:
            return (
                False,
                delta,
                f"HEAP COLLISION RISK: Delta {delta} B between Slot 2 (0x{slot2_ptr:08X}) "
                f"and Slot 21 (0x{slot21_ptr:08X}) is less than required model size ({min_separation} B). "
                f"Will trigger LoadGeoPalette double-relocation bug (0xebca805e).",
            )

        return (
            True,
            delta,
            f"Verified safe heap separation: Delta {delta} B (>= {min_separation} B) "
            f"between Slot 2 (0x{slot2_ptr:08X}) and Slot 21 (0x{slot21_ptr:08X}).",
        )


# Aliases for auditor subsystems
PointerRelocationAuditor = ModelRelocationAuditor
HeapSeparationAuditor = ModelRelocationAuditor

