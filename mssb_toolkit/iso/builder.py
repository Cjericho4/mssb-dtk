"""End-to-End GameCube ISO Rebuilder and Integrity Verification Suite for MSSB (USA GYQE01)."""

from __future__ import annotations

import os
import shutil
import struct
from typing import Any, Dict, Optional, Tuple

from mssb_toolkit.compression.lzss import ArchiveDecompressor, NamcoLZSSEncoder
from mssb_toolkit.iso.patcher import (
    DISC_SEC1_SLOT2,
    DISC_SEC1_SLOT21,
    DISC_SEC2_SLOT2,
    DISC_SEC2_SLOT21,
    DOL_EXPECTED_SIZE,
    DOLPatcher,
    ISOPatcher,
)


class ISOBuilder:
    """Constructs fully synchronized, playable GameCube ISOs with dual-section models."""

    @classmethod
    def build_synchronized_iso(
        cls,
        source_iso_path: str,
        output_iso_path: str,
        slot2_compressed_chunk: Optional[bytes] = None,
        slot21_compressed_chunk: Optional[bytes] = None,
        patch_dol: bool = True,
    ) -> Dict[str, Any]:
        """Build a clean custom ISO with synchronized Section 1 & Section 2 character payloads."""
        if not os.path.exists(source_iso_path):
            raise FileNotFoundError(f"Source ISO not found: {source_iso_path}")

        # Step 1: Clone source ISO to destination if distinct
        if os.path.abspath(source_iso_path) != os.path.abspath(output_iso_path):
            shutil.copyfile(source_iso_path, output_iso_path)

        # Step 2: Patch main.dol data tables if requested
        dol_status = None
        if patch_dol:
            with open(output_iso_path, "rb") as f:
                f.seek(0x420)
                dol_off = struct.unpack(">I", f.read(4))[0]
                f.seek(dol_off)
                orig_dol = f.read(DOL_EXPECTED_SIZE)

            patched_dol = DOLPatcher.patch_character_descriptors(orig_dol, slot_id=21)
            is_safe, diffs, err = DOLPatcher.verify_dol_safety(orig_dol, patched_dol)
            # If already patched, diffs may be 0, otherwise verify safety
            if not is_safe and len(diffs) > 0:
                raise RuntimeError(f"DOL safety verification failed: {err}")

            ISOPatcher.burn_main_dol_to_iso(output_iso_path, patched_dol)
            dol_status = {"dol_offset": dol_off, "diff_count": len(diffs), "diffs": [hex(x) for x in diffs]}

        # Step 3: Burn Slot 2 model if provided
        slot2_status = None
        if slot2_compressed_chunk is not None:
            slot2_status = ISOPatcher.burn_slot_payload_to_iso(
                output_iso_path, slot_id=2, compressed_payload=slot2_compressed_chunk, target_size=86068
            )

        # Step 4: Burn Slot 21 model if provided
        slot21_status = None
        if slot21_compressed_chunk is not None:
            slot21_status = ISOPatcher.burn_slot_payload_to_iso(
                output_iso_path, slot_id=21, compressed_payload=slot21_compressed_chunk, target_size=86068
            )

        # Step 5: Perform full post-build audit
        audit_res = cls.verify_iso_integrity(
            output_iso_path,
            verify_slot2=slot2_compressed_chunk is not None,
            verify_slot21=slot21_compressed_chunk is not None,
        )

        return {
            "output_iso": output_iso_path,
            "dol_status": dol_status,
            "slot2_burn": slot2_status,
            "slot21_burn": slot21_status,
            "audit": audit_res,
        }

    @classmethod
    def verify_iso_integrity(
        cls,
        iso_path: str,
        verify_slot2: bool = True,
        verify_slot21: bool = True,
        chunk_read_size: int = 86080,
    ) -> Dict[str, Any]:
        """Perform bit-exact forensic verification on built ISO."""
        results: Dict[str, Any] = {}

        with open(iso_path, "rb") as f:
            # Check Game ID
            f.seek(0)
            game_id = f.read(6).decode("ascii", errors="ignore")
            results["game_id"] = game_id

            if verify_slot2:
                f.seek(DISC_SEC1_SLOT2)
                s1_chunk = f.read(chunk_read_size)
                f.seek(DISC_SEC2_SLOT2)
                s2_chunk = f.read(chunk_read_size)
                results["slot2_synchronized"] = (s1_chunk == s2_chunk)
                # Decompress via ArchiveDecompressor
                dec2 = ArchiveDecompressor(s1_chunk, 11, 4, 119736).decompress()
                results["slot2_decomp_size"] = len(dec2)
                results["slot2_decomp_valid"] = (len(dec2) == 119736)

            if verify_slot21:
                f.seek(DISC_SEC1_SLOT21)
                s1_chunk = f.read(chunk_read_size)
                f.seek(DISC_SEC2_SLOT21)
                s2_chunk = f.read(chunk_read_size)
                results["slot21_synchronized"] = (s1_chunk == s2_chunk)
                # Decompress via ArchiveDecompressor
                dec21 = ArchiveDecompressor(s1_chunk, 11, 4, 119736).decompress()
                results["slot21_decomp_size"] = len(dec21)
                results["slot21_decomp_valid"] = (len(dec21) == 119736)

        return results
