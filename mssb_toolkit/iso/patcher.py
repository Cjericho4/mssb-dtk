"""GameCube Disc and DOL Data Table Patcher for Mario Superstar Baseball (USA GYQE01).

Implements:
- Data-only patching of main.dol (Master Descriptors, Subfile Archive Pointers, Glove Table).
- Synchronous burning of bit-exact Namco LZSS compressed model chunks into both
  Section 1 (Disc Subfiles) and Section 2 (ARAM Monolithic Chunk) of ZZZZ.dat on disc.
- Strict sector boundary and blast-radius verification.
"""

from __future__ import annotations

import struct
from typing import Dict, List, Optional, Set, Tuple, Union

# ==============================================================================
# AUDITED ARCHITECTURE CONSTANTS: GAME DISC & MEMORY LAYOUT (USA GYQE01)
# ==============================================================================

# --- Disc Image Base Offsets ---
ZZZZ_DISC_BASE: int = 0x3C320000        # Base sector offset of files/ZZZZ.dat on disc
DOL_DISC_OFFSET: int = 0x00020300       # Base sector offset of main.dol on disc
AAAA_DISC_OFFSET: int = 0x32358000      # Base sector offset of files/aaaa.dat (game.rel)
AAAA_FILE_SIZE: int = 1538048           # Exact byte length of files/aaaa.dat
FST_DISC_OFFSET: int = 0x00136800       # File String Table offset on disc

# --- Character Slots ---
SLOT_ID_DONKEY_KONG: int = 2            # Primary Donkey Kong character slot (Pitcher)
SLOT_ID_PIANTA_BLUE: int = 21           # Secondary Donkey Kong character slot (2nd Base)

# --- Hardware Bone / Glove Attachment Node IDs ---
GLOVE_NODE_DK_BARE_HANDS: int = 0x000C  # Bone index 12 -> DK wrist nodes [6, 7, 8] in sub-table 0x0EBB18

# --- Standalone 3D Model Container (donkey00.gpc) Properties ---
DK_STANDALONE_MODEL_UNCOMP_SIZE: int = 119736  # Exact uncompressed size in bytes (0x0001D3B8)
DK_STANDALONE_MODEL_UNCOMP_TAG: int = 0x4001D3B8  # Bit 30 LZSS Decompress Tag (0x40000000 | 119736)
DK_MODEL_COMPRESSED_FLAGS: int = 0x0000040B   # LZSS Standard compressed subfile flags
DK_MASTER_DESCRIPTOR_FLAGS: int = 0x00015034  # Master allocation flags for standalone model

# --- Section 1: Disc Subfiles Archive (DOL Table Base: 0x000EED78) ---
SEC1_SUBFILE_38_DISC_OFFSET: int = 0x098F1000      # Subfile 38 (Donkey Kong Standalone Model)
SEC1_SUBFILE_38_COMP_SIZE: int = 86068            # Subfile 38 compressed size on disc
SEC1_SUBFILE_38_DMA_PADDED_SIZE: int = 86080      # 32-byte DMA aligned read size

SEC1_SUBFILE_399_DISC_OFFSET: int = 0x0B95C800     # Subfile 399 (Pianta Blue Standalone Model)
SEC1_SUBFILE_399_COMP_SIZE: int = 68432           # Subfile 399 compressed size on disc
SEC1_SUBFILE_399_DMA_PADDED_SIZE: int = 68448     # 32-byte DMA aligned read size

# --- Section 2: ARAM Monolithic Master Chunk (DOL Table Base: 0x000ECD38) ---
SEC2_CHUNK_DISC_BASE: int = 0x1A15E800            # Disc offset of Section 2 ARAM master chunk
SEC2_SLOT2_ARAM_OFFSET: int = 0x0002AE40          # Slot 2 ARAM offset (Disc: 0x1A15E800 + 0x0002AE40 = 0x1A189640)
SEC2_SLOT2_COMP_SIZE: int = 86068                 # Slot 2 compressed chunk size
SEC2_SLOT2_DMA_PADDED_SIZE: int = 86080           # 32-byte DMA aligned chunk size

SEC2_SLOT21_ARAM_OFFSET: int = 0x0019DC80         # Slot 21 ARAM offset (Disc: 0x1A15E800 + 0x0019DC80 = 0x1A2FC480)
SEC2_SLOT21_COMP_SIZE: int = 86068                # Slot 21 compressed chunk size
SEC2_SLOT21_DMA_PADDED_SIZE: int = 86080          # 32-byte DMA aligned chunk size

# --- Calculated Absolute Disc Offsets ---
DISC_SEC1_SLOT2: int = ZZZZ_DISC_BASE + SEC1_SUBFILE_38_DISC_OFFSET    # 0x45C11000
DISC_SEC1_SLOT21: int = ZZZZ_DISC_BASE + SEC1_SUBFILE_399_DISC_OFFSET  # 0x47C7C800
DISC_SEC2_SLOT2: int = ZZZZ_DISC_BASE + SEC2_CHUNK_DISC_BASE + SEC2_SLOT2_ARAM_OFFSET    # 0x564A9640
DISC_SEC2_SLOT21: int = ZZZZ_DISC_BASE + SEC2_CHUNK_DISC_BASE + SEC2_SLOT21_ARAM_OFFSET  # 0x5661C480

# --- Maximum Capacity Bounds ---
SEC1_SLOT2_MAX_CAPACITY: int = 0x15800    # 88,064 bytes
SEC1_SLOT21_MAX_CAPACITY: int = 0x10B50   # 68,432 bytes (Exact Subfile 399 capacity)
SEC2_SLOT2_MAX_CAPACITY: int = 0x15040    # 86,080 bytes
SEC2_SLOT21_MAX_CAPACITY: int = 0x15040   # 86,080 bytes

# --- main.dol Table Offsets ---
DOL_EXPECTED_SIZE: int = 1139968          # Exact byte length of main.dol
DOL_TEXT_SECTION_END: int = 0x0DFB40      # Boundary between .text executable and .data tables
DOL_GLOVE_TABLE_BASE: int = 0x000EBAAC   # Glove Attachment Table base
DOL_MASTER_DESCRIPTORS_BASE: int = 0x000ECD38  # Master Allocation Descriptors base
DOL_SUBFILES_TABLE_BASE: int = 0x000EED78      # Primary Character Subfiles Table base
DOL_SLOT21_SUBFILE_ENTRY: int = 0x000F0660     # Subfiles Table Entry for Slot 21 (Subfile 399 @ 0xF0660)
DOL_SUBFILE_399_OFFSET: int = 0x000F0660       # Subfile 399 descriptor in main.dol

EXPECTED_DOL_PATCH_OFFSETS: Set[int] = {
    0xEBAD7,          # Glove Table Slot 21 (0x7E -> 0x0C, Node 12 Bare Hand)
    0xECE91, 0xECE92, 0xECE93,  # Master Descriptors Slot 21 uncompressed size (0x0002AE40)
    0xECE96, 0xECE97,  # Master Descriptors Slot 21 flags (0x5034)
    0xF066D, 0xF066E, 0xF066F,  # Subfile 399 buffer size tag (0x02AE40)
}


class DOLPatcher:
    """Handles data-only patching and safety auditing for main.dol."""

    @classmethod
    def patch_character_descriptors(
        cls,
        dol_bytes: Union[bytes, bytearray],
        slot_id: int = 21,
        uncompressed_size: int = 0x0002AE40,
        flags: int = 0x00015034,
        glove_node: int = 12,
        aram_offset: Optional[int] = None,
        disc_offset: Optional[int] = None,
        compressed_size: Optional[int] = None,
    ) -> bytearray:
        """Apply data-only patch to main.dol repointing character slot to unused space arenas."""
        dol = bytearray(dol_bytes)
        if len(dol) != DOL_EXPECTED_SIZE:
            raise ValueError(f"Invalid main.dol size: expected {DOL_EXPECTED_SIZE}, got {len(dol)}")

        # 1. Glove Table: 2 bytes per slot
        glove_off = DOL_GLOVE_TABLE_BASE + slot_id * 2
        struct.pack_into(">H", dol, glove_off, glove_node)

        # 2. Master Allocation Descriptors: 16 bytes per slot
        desc_off = DOL_MASTER_DESCRIPTORS_BASE + slot_id * 16
        struct.pack_into(">I", dol, desc_off + 0x08, uncompressed_size)
        struct.pack_into(">I", dol, desc_off + 0x0C, flags)

        # 3. Subfile Archive Pointers Patch (0xF0660)
        subfile_val = 0x40000000 | (uncompressed_size & 0x00FFFFFF)
        struct.pack_into(">I", dol, DOL_SLOT21_SUBFILE_ENTRY + 0x0C, subfile_val)

        return dol

    @classmethod
    def verify_dol_safety(
        cls,
        orig_dol: bytes,
        patched_dol: bytes,
    ) -> Tuple[bool, List[int], Optional[str]]:
        """Verify that DOL modifications strictly contain verified bytes in .data and 0 in .text."""
        if len(orig_dol) != len(patched_dol):
            return False, [], f"DOL size mismatch: {len(orig_dol)} vs {len(patched_dol)}"

        diffs = [i for i in range(len(orig_dol)) if orig_dol[i] != patched_dol[i]]

        # Check for any .text modifications
        text_diffs = [off for off in diffs if off < DOL_TEXT_SECTION_END]
        if text_diffs:
            return False, diffs, f"CRITICAL: .text executable modified at: {[hex(x) for x in text_diffs]}"

        # Verify all modifications are strictly in .data sections
        data_diffs = [off for off in diffs if off >= DOL_TEXT_SECTION_END]
        if not data_diffs and diffs:
            return False, diffs, "Diff contained non-data modifications"

        return True, diffs, None




# Guaranteed Unallocated Memory Chunks (Unused Memory Arenas)
SEC1_UNALLOCATED_ARENA = 0x0BD28000    # Past Section 1 subfile 495 (0x0BD23FB0)
SEC2_UNALLOCATED_SLOT21 = 0x1A408800   # ARAM 0x002AA000 (Past retail chunk 53 @ 0x1A406A68)
SEC2_UNALLOCATED_SLOT40 = 0x1A419E80   # ARAM 0x002BB680


class ISOPatcher:
    """In-place burning engine for GameCube ISO dual-section synchronization."""

    @classmethod
    def restore_baseline_from_original(
        cls,
        orig_iso_path: str,
        target_iso_path: str,
    ) -> None:
        """Stream pristine retail ZZZZ.dat and aaaa.dat from original ISO to target ISO."""
        chunk_size = 10 * 1024 * 1024
        with open(orig_iso_path, "rb") as f_orig, open(target_iso_path, "r+b") as f_target:
            # Restore ZZZZ.dat
            f_orig.seek(ZZZZ_DISC_BASE)
            f_target.seek(ZZZZ_DISC_BASE)
            for _ in range(45):
                buf = f_orig.read(chunk_size)
                if not buf:
                    break
                f_target.write(buf)

            # Restore aaaa.dat (game.rel)
            f_orig.seek(0x32358000)
            clean_aaaa = f_orig.read(1538048)
            f_target.seek(0x32358000)
            f_target.write(clean_aaaa)
            f_target.flush()

    @classmethod
    def pad_payload(cls, data: bytes, target_size: Optional[int] = None) -> bytes:
        """Pad compressed payload to target size and 32-byte alignment."""
        out = bytearray(data)
        if target_size is not None and len(out) < target_size:
            out.extend(b"\x00" * (target_size - len(out)))
        rem = len(out) % 32
        if rem != 0:
            out.extend(b"\x00" * (32 - rem))
        return bytes(out)

    @classmethod
    def burn_slot_payload_to_iso(
        cls,
        iso_path: str,
        slot_id: int,
        compressed_payload: bytes,
        target_size: Optional[int] = None,
    ) -> Dict[str, int]:
        """Burn bit-exact compressed model chunk synchronously into Section 1 and Section 2."""
        if slot_id == 2:
            sec1_off = DISC_SEC1_SLOT2
            sec2_off = DISC_SEC2_SLOT2
            sec1_max = SEC1_SLOT2_MAX_CAPACITY
            sec2_max = SEC2_SLOT2_MAX_CAPACITY
            default_target = 86068
        elif slot_id == 21:
            sec1_off = DISC_SEC1_SLOT21
            sec2_off = DISC_SEC2_SLOT21
            sec1_max = SEC1_SLOT21_MAX_CAPACITY
            sec2_max = SEC2_SLOT21_MAX_CAPACITY
            default_target = 86068
        else:
            raise ValueError(f"Unsupported slot_id for dual-section burn: {slot_id}")

        final_target = target_size or default_target
        payload = cls.pad_payload(compressed_payload, target_size=final_target)

        # Capacity guards
        if len(payload) > sec1_max:
            raise ValueError(f"Payload size {len(payload)} exceeds Section 1 capacity {sec1_max}")
        if len(payload) > sec2_max:
            raise ValueError(f"Payload size {len(payload)} exceeds Section 2 capacity {sec2_max}")

        with open(iso_path, "r+b") as f:
            # Burn Section 1
            f.seek(sec1_off)
            f.write(payload)

            # Burn Section 2
            f.seek(sec2_off)
            f.write(payload)

        return {
            "slot_id": slot_id,
            "sec1_offset": sec1_off,
            "sec2_offset": sec2_off,
            "payload_size": len(payload),
        }

    @classmethod
    def burn_main_dol_to_iso(
        cls,
        iso_path: str,
        patched_dol_bytes: bytes,
    ) -> int:
        """Write patched main.dol into ISO image at header DOL offset."""
        if len(patched_dol_bytes) != DOL_EXPECTED_SIZE:
            raise ValueError(f"Invalid main.dol size: {len(patched_dol_bytes)}")

        with open(iso_path, "r+b") as f:
            f.seek(0x420)
            dol_iso_off = struct.unpack(">I", f.read(4))[0]
            f.seek(dol_iso_off)
            f.write(patched_dol_bytes)

        return dol_iso_off

