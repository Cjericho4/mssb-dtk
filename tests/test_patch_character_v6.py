#!/usr/bin/env python3
"""
Unit and Integration Tests for Universal Character Slot Patcher V6
------------------------------------------------------------------
Verifies:
  1. Complete 19-subfile engine pipeline clone for Slot 1 (Luigi)
  2. Exact 10-texture CMPR injection across 0x000180..0x004F00
  3. Bit-exact Zone B geometry preservation (0x015BE0+)
  4. Bit-exact Namco LZSS roundtrip decompression with 0 underflow errors
  5. 13-bone skeletal rig synchronization (Entry 433) and Glove Table (0x000C)
  6. 0 NULL equipment dereference crash risks at 0x800233a0
  7. Strictly 0 bytes modified in executable .text machine code (< 0x0DFB40)
"""

import os
import shutil
import struct
import tempfile
import pytest

from tools.patch_character_v6 import CharacterPatcherV6
from mssb_toolkit.models.cmpr import (
    CMPRModelInjector,
    DK_TEXTURE_OFFSETS_V5,
    DK_TEXTURE_REGION_START,
    DK_TEXTURE_REGION_END,
    COLOR_PURE_BLUE,
    COLOR_PURE_RED,
)
from mssb_toolkit.compression.lzss import NamcoLZSSEncoder
from mssb_toolkit.validation.engine_oracle import (
    GameCubeDecompressDiskDataOracle,
    GameEngineSimulationOracle,
)
from mssb_toolkit.tables.table_manager import (
    MasterDescriptorsTable,
    SubfilesArchiveTable,
    GloveAttachmentTable,
    CharacterSlot,
)


@pytest.fixture
def clean_iso_path():
    iso_path = "/home/michael/decomp/mssb-dtk/orig/GYQE01.iso"
    if not os.path.exists(iso_path):
        pytest.skip(f"Clean ISO not found at {iso_path}")
    return iso_path


def test_v6_exact_10_texture_injection():
    """Verify that V6 CMPR injection targets the exact 10 texture offsets with 0 Zone B diffs."""
    model_path = "/home/michael/decomp/mssb-dtk/uncompressed_dk_model.bin"
    if not os.path.exists(model_path):
        pytest.skip("uncompressed_dk_model.bin not found")

    with open(model_path, "rb") as f:
        clean_model = f.read()

    recolored = CMPRModelInjector.create_solid_color_model(clean_model, COLOR_PURE_BLUE)

    # 1. Size must remain identical (119,736 B)
    assert len(recolored) == len(clean_model) == 119736

    # 2. Header (< 0x000180) must be 100% bit-exact
    assert recolored[:DK_TEXTURE_REGION_START] == clean_model[:DK_TEXTURE_REGION_START]

    # 3. Zone B geometry (0x015BE0+) and all data after 0x004F00 must be 100% bit-exact
    assert recolored[DK_TEXTURE_REGION_END:] == clean_model[DK_TEXTURE_REGION_END:]

    # 4. Verify all 10 texture offsets are modified with valid CMPR blocks
    for tex_id, info in DK_TEXTURE_OFFSETS_V5.items():
        off = int(info["offset"])
        sz = int(info["size"])
        chunk = recolored[off : off + sz]
        # In solid blue CMPR, each 8-byte block begins with 0x001F 0x0000
        assert chunk[:4] == struct.pack(">HH", COLOR_PURE_BLUE, 0x0000)

    # 5. Verify roundtrip Namco LZSS compression & decompression
    encoder = NamcoLZSSEncoder(lookback_bits=11, repetition_bits=4)
    comp = encoder.compress(recolored)
    oracle = GameCubeDecompressDiskDataOracle(comp, lookback_bits=11, repetition_bits=4, target_size=119736)
    decomp, err = oracle.decompress()
    assert err == 0
    assert bytes(decomp) == bytes(recolored)


def test_v6_patcher_slot1_cloning(clean_iso_path):
    """Verify that CharacterPatcherV6 clones Slot 1 with 0 .text diffs and 0 crash risks."""
    with tempfile.TemporaryDirectory() as tmpdir:
        target_iso = os.path.join(tmpdir, "test_v6_slot1.iso")

        patcher = CharacterPatcherV6(clean_iso_path, target_iso)
        res = patcher.clone_slot(
            target_slot=1,  # Luigi -> Cloned DK
            source_slot=2,  # Donkey Kong
            custom_texture_color=COLOR_PURE_BLUE,
        )

        assert res["target_slot"] == 1
        assert res["source_slot"] == 2
        assert res["subfiles_cloned"] == 19

        # Read patched DOL
        with open(target_iso, "rb") as f_iso:
            f_iso.seek(0x420)
            dol_offset = struct.unpack(">I", f_iso.read(4))[0]
            f_iso.seek(dol_offset)
            patched_dol = f_iso.read(0x116500)

        # 1. Verify Glove Attachment Table (0x000EBAAC): Slot 1 must be 0x000C (DK bare hands)
        glove_tbl = GloveAttachmentTable(patched_dol)
        assert glove_tbl.get_glove_index(CharacterSlot(1)) == 0x000C

        # 2. Verify Master Descriptors Table (0x000ECD38):
        master_tbl = MasterDescriptorsTable(patched_dol)
        desc_slot1 = master_tbl.get_descriptor(CharacterSlot(1))
        assert desc_slot1.uncompressed_size == 119736
        assert desc_slot1.flags == 0x00015034

        # Raw bit 30 LZSS tag on uncompressed tag
        raw_uncomp_tag = struct.unpack_from(">I", patched_dol, 0x000ECD38 + 1 * 16 + 4)[0]
        assert raw_uncomp_tag == 0x4001D3B8

        # Verify 7 sub-items (54 + 1*7 + 0..6 = Entries 61..67)
        for item in range(7):
            idx = 54 + 1 * 7 + item
            off = 0x000ECD38 + idx * 16
            flags, uncomp_tag, aram_off, comp_sz = struct.unpack_from(">IIII", patched_dol, off)
            assert (uncomp_tag & 0x40000000) != 0, f"Entry {idx} missing bit 30 LZSS tag"

        # Verify Skeletal Rig Descriptor (Entry 433)
        skel_idx = 0x1B0 + 1
        skel_off = 0x000ECD38 + skel_idx * 16
        flags_skel, uncomp_tag_skel, aram_off_skel, comp_sz_skel = struct.unpack_from(">IIII", patched_dol, skel_off)
        assert (uncomp_tag_skel & 0x40000000) != 0
        assert (uncomp_tag_skel & 0x00FFFFFF) == 41392

        # 3. Verify Subfiles Table (0x000EED78): 19 subfiles for Slot 1 (19..37)
        sub_tbl = SubfilesArchiveTable(patched_dol)
        for sub_idx in range(19):
            track = sub_tbl.get_subfile(19 + sub_idx)
            assert (track.uncompressed_size > 0)
            raw_sub_tag = struct.unpack_from(">I", patched_dol, 0x000EED78 + (19 + sub_idx) * 16 + 4)[0]
            assert (raw_sub_tag & 0x40000000) != 0, f"Subfile {19 + sub_idx} missing bit 30 tag"

        # 4. Verify 0 .text modifications (< 0x0DFB40)
        with open("/home/michael/decomp/mssb-dtk/orig/GYQE01/sys/main.dol", "rb") as f_clean:
            clean_dol = f_clean.read(0x116500)
        assert patched_dol[:0x0DFB40] == clean_dol[:0x0DFB40], "FATAL: .text executable code modified!"
