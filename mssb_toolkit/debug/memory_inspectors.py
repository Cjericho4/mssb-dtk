"""Real-Time GameCube RAM Subsystem Inspectors.

Provides real-time inspectors for:
- Subfile Archive Table (0x800EED78)
- Master Allocation Descriptors (0x800ECD38)
- Glove & Bone Attachment Tables (0x800EBAAC & 0x800EBB18)
- Character Staging & Animation State Machine (0x8036E548 hugeAnimStruct)
- Player Struct Table (0x8036F14C)
- Batting Style Hook Table (0x80001840)
"""

from __future__ import annotations

import struct
from dataclasses import dataclass, field
from typing import Any, Dict, List, Optional

from mssb_toolkit.debug.memory_hook import GameCubeMemoryHook


@dataclass
class SubfileEntry:
    """Entry in Subfile Archive Table (0x800EED78)."""

    slot_id: int
    flags: int
    uncompressed_size: int
    is_compressed: bool
    compressed_offset: int
    compressed_size: int

    @property
    def raw_size(self) -> int:
        return self.uncompressed_size & 0x00FFFFFF


@dataclass
class MasterDescriptorEntry:
    """Entry in Master Allocation Descriptors Table (0x800ECD38)."""

    slot_id: int
    flags: int
    uncompressed_size: int
    aram_offset: int
    flags_capacity: int


@dataclass
class GloveAttachmentEntry:
    """Entry in Glove & Bone Attachment Table (0x800EBAAC -> 0x800EBB18)."""

    slot_id: int
    glove_index: int
    bones: List[int]
    is_safe: bool
    description: str = ""


@dataclass
class CharacterStagingState:
    """Staging and DMA state from hugeAnimStruct (0x8036E548)."""

    load_mode: int
    staged_slots: List[int]
    active_loading_index: int
    aram_transfer_phase: int
    staging_state: int


@dataclass
class PlayerEntity:
    """Live match active diamond player entity from Player Struct Table (0x8036F14C)."""

    player_index: int
    struct_addr: int
    model_buffer_ptr: int
    character_id: int
    fielding_position: int


class GameCubeInspectors:
    """Real-time memory inspectors for Mario Superstar Baseball data structures in RAM."""

    SUBFILES_TABLE_ADDR = 0x800EED78
    MASTER_DESCRIPTORS_ADDR = 0x800ECD38
    GLOVE_TABLE_ADDR = 0x800EBAAC
    GLOVE_SUB_TABLE_ADDR = 0x800EBB18
    HUGE_ANIM_STRUCT_ADDR = 0x8036E548
    PLAYER_STRUCT_TABLE_ADDR = 0x8036F14C
    BATTING_STYLE_TABLE_ADDR = 0x80001840

    def __init__(self, hook: GameCubeMemoryHook):
        self.hook = hook

    def inspect_subfile_table(self, num_entries: int = 54) -> List[SubfileEntry]:
        """Inspect Subfiles Archive Table at 0x800EED78."""
        entries: List[SubfileEntry] = []
        for slot in range(num_entries):
            addr = self.SUBFILES_TABLE_ADDR + slot * 16
            raw = self.hook.read_bytes(addr, 16)
            flags, uncomp_sz, comp_off, comp_sz = struct.unpack(">IIII", raw)
            is_compressed = bool(uncomp_sz & 0x40000000)
            entries.append(
                SubfileEntry(
                    slot_id=slot,
                    flags=flags,
                    uncompressed_size=uncomp_sz,
                    is_compressed=is_compressed,
                    compressed_offset=comp_off,
                    compressed_size=comp_sz,
                )
            )
        return entries

    def inspect_master_descriptors(self, num_entries: int = 54) -> List[MasterDescriptorEntry]:
        """Inspect Master Allocation Descriptors at 0x800ECD38."""
        entries: List[MasterDescriptorEntry] = []
        for slot in range(num_entries):
            addr = self.MASTER_DESCRIPTORS_ADDR + slot * 16
            raw = self.hook.read_bytes(addr, 16)
            flags, uncomp_sz, aram_off, flags_cap = struct.unpack(">IIII", raw)
            entries.append(
                MasterDescriptorEntry(
                    slot_id=slot,
                    flags=flags,
                    uncompressed_size=uncomp_sz,
                    aram_offset=aram_off,
                    flags_capacity=flags_cap,
                )
            )
        return entries

    def inspect_glove_attachment(
        self,
        slot_id: int,
        max_bones: int = 13,
    ) -> GloveAttachmentEntry:
        """Inspect Glove bone attachment for character slot."""
        idx_addr = self.GLOVE_TABLE_ADDR + slot_id * 2
        g_idx = self.hook.read_u16(idx_addr)

        sub_addr = self.GLOVE_SUB_TABLE_ADDR + g_idx
        raw = self.hook.read_bytes(sub_addr, 6)
        b1, b2, b3 = struct.unpack(">HHH", raw)

        is_safe = (b1 < max_bones and b2 < max_bones and b3 < max_bones)
        desc = (
            "Safe bone binding"
            if is_safe
            else f"INVALID BONE: [{b1}, {b2}, {b3}] exceeds max skeleton bones ({max_bones})"
        )

        return GloveAttachmentEntry(
            slot_id=slot_id,
            glove_index=g_idx,
            bones=[b1, b2, b3],
            is_safe=is_safe,
            description=desc,
        )

    def inspect_all_glove_attachments(
        self,
        num_entries: int = 54,
        slot_bone_limits: Optional[Dict[int, int]] = None,
    ) -> List[GloveAttachmentEntry]:
        """Inspect all glove table entries."""
        limits = slot_bone_limits or {}
        entries = []
        for slot in range(num_entries):
            max_b = limits.get(slot, 13)
            entries.append(self.inspect_glove_attachment(slot_id=slot, max_bones=max_b))
        return entries

    def inspect_character_staging(self) -> CharacterStagingState:
        """Read character staging state from hugeAnimStruct at 0x8036E548."""
        load_mode = self.hook.read_u8(self.HUGE_ANIM_STRUCT_ADDR + 0x2D7C)
        staged_bytes = self.hook.read_bytes(self.HUGE_ANIM_STRUCT_ADDR + 0x2D7F, 9)
        staged_slots = list(staged_bytes)
        active_idx = self.hook.read_u8(self.HUGE_ANIM_STRUCT_ADDR + 0x2D88)
        aram_phase = self.hook.read_u8(self.HUGE_ANIM_STRUCT_ADDR + 0x2D8D)
        staging_state = self.hook.read_u8(self.HUGE_ANIM_STRUCT_ADDR + 0x2D8E)

        return CharacterStagingState(
            load_mode=load_mode,
            staged_slots=staged_slots,
            active_loading_index=active_idx,
            aram_transfer_phase=aram_phase,
            staging_state=staging_state,
        )

    def inspect_player_entities(self, num_players: int = 18) -> List[PlayerEntity]:
        """Inspect active match player entity structs at 0x8036F14C."""
        entities: List[PlayerEntity] = []
        stride = 0x27C
        for i in range(num_players):
            base = self.PLAYER_STRUCT_TABLE_ADDR + i * stride
            model_ptr = self.hook.read_u32(base + 0x008)
            char_id = self.hook.read_u16(base + 0x252)
            pos_id = self.hook.read_u16(base + 0x254)
            entities.append(
                PlayerEntity(
                    player_index=i,
                    struct_addr=base,
                    model_buffer_ptr=model_ptr,
                    character_id=char_id,
                    fielding_position=pos_id,
                )
            )
        return entities

    def inspect_batting_styles(self, num_entries: int = 54) -> List[int]:
        """Inspect g_CharBatStyle table at 0x80001840."""
        raw = self.hook.read_bytes(self.BATTING_STYLE_TABLE_ADDR, num_entries)
        return list(raw)
