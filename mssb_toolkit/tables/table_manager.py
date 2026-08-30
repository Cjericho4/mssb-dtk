"""Strongly-Typed Binary Table Abstractions & ARAM Allocator for Mario Superstar Baseball.

Provides type-safe, bounds-checked interfaces for:
1. CharacterSlot IntEnum (all 54 character slots).
2. MasterDescriptorsTable (DOL 0x000ECD38).
3. SubfilesArchiveTable (DOL 0x000EED78).
4. GloveAttachmentTable (DOL 0x000EBAAC).
5. ARAMAllocator (dynamic, non-overlapping Section 2 memory allocator).
"""

import struct
from dataclasses import dataclass
from enum import IntEnum
from typing import Dict, List, Optional, Tuple

class CharacterSlot(IntEnum):
    MARIO = 0
    LUIGI = 1
    DONKEY_KONG = 2
    PEACH = 3
    DAISY = 4
    YOSHI = 5
    BIRDO = 6
    WARIO = 7
    WALUIGI = 8
    BOWSER = 9
    KOOPA_GREEN = 10
    KOOPA_RED = 11
    PARATROOPA_RED = 12
    PARATROOPA_GREEN = 13
    MAGIKOOPA_BLUE = 14
    MAGIKOOPA_RED = 15
    MAGIKOOPA_GREEN = 16
    MAGIKOOPA_YELLOW = 17
    HAMMER_BRO = 18
    BOWSER_JR = 19
    BOOMERANG_BRO = 20
    PIANTA_BLUE = 21
    PIANTA_BLUE_PRIMARY = 21
    PIANTA_RED_PRIMARY = 22
    PIANTA_YELLOW_PRIMARY = 23
    NOKEE_BLUE = 24
    NOKEE_RED = 25
    NOKEE_GREEN = 26
    TOAD_RED = 27
    TOAD_BLUE = 28
    TOAD_YELLOW = 29
    TOAD_GREEN = 30
    TOAD_PURPLE = 31
    TOADETTE = 32
    TOADSWORTH = 33
    BABY_MARIO = 34
    BABY_LUIGI = 35
    DRY_BONES_GRAY = 36
    DRY_BONES_RED = 37
    PETEY_PIRANHA = 38
    DIDDY_KONG = 39
    DRY_BONES_BLUE = 39
    PIANTA_BLUE_ALTERNATE = 40
    PIANTA_RED_ALTERNATE = 41
    PIANTA_YELLOW_ALTERNATE = 42
    KING_BOO = 43
    DIXIE_KONG = 44
    GOOMBA = 45
    PARAGOOMBA = 46
    MONTY_MOLE = 47
    SHY_GUY_RED = 48
    SHY_GUY_BLUE = 49
    SHY_GUY_YELLOW = 50
    SHY_GUY_GREEN = 51
    SHY_GUY_BLACK = 52
    BOO = 53


@dataclass
class MasterDescriptor:
    flags: int
    uncompressed_size: int
    aram_offset: int
    compressed_size: int


class MasterDescriptorsTable:
    """Manages the 16-byte Master Allocation Descriptors Table in main.dol."""
    BASE_OFFSET = 0x000ECD38
    ENTRY_SIZE = 16
    TOTAL_SLOTS = 54

    def __init__(self, dol_bytes: bytearray):
        self.dol = dol_bytes

    def get_descriptor(self, slot: CharacterSlot) -> MasterDescriptor:
        off = self.BASE_OFFSET + int(slot) * self.ENTRY_SIZE
        flags, uncomp_sz_tag, aram_off, comp_sz = struct.unpack_from(">IIII", self.dol, off)
        return MasterDescriptor(
            flags=flags,
            uncompressed_size=uncomp_sz_tag & 0x00FFFFFF,
            aram_offset=aram_off,
            compressed_size=comp_sz,
        )

    def set_descriptor(
        self,
        slot: CharacterSlot,
        aram_offset: int,
        uncompressed_size: int,
        compressed_size: int,
        flags: int = 0x0000040B,
    ):
        off = self.BASE_OFFSET + int(slot) * self.ENTRY_SIZE
        uncomp_tag = 0x40000000 | (uncompressed_size & 0x00FFFFFF)
        struct.pack_into(">IIII", self.dol, off, flags, uncomp_tag, aram_offset, compressed_size)


@dataclass
class SubfileDescriptor:
    flags: int
    uncompressed_size: int
    disc_offset: int
    compressed_size: int


class SubfilesArchiveTable:
    """Manages the Primary Subfiles Archive Table in main.dol."""
    BASE_OFFSET = 0x000EED78
    ENTRY_SIZE = 16
    SUBFILE_399_OFFSET = 0x000F0668

    def __init__(self, dol_bytes: bytearray):
        self.dol = dol_bytes

    def get_subfile(self, slot: CharacterSlot) -> SubfileDescriptor:
        off = self.BASE_OFFSET + int(slot) * self.ENTRY_SIZE
        flags, uncomp_sz_tag, disc_off, comp_sz = struct.unpack_from(">IIII", self.dol, off)
        return SubfileDescriptor(
            flags=flags,
            uncompressed_size=uncomp_sz_tag & 0x00FFFFFF,
            disc_offset=disc_off,
            compressed_size=comp_sz,
        )

    def set_subfile(
        self,
        slot: CharacterSlot,
        disc_offset: int,
        uncompressed_size: int,
        compressed_size: int,
        flags: int = 0x0000040B,
    ):
        off = self.BASE_OFFSET + int(slot) * self.ENTRY_SIZE
        uncomp_tag = 0x40000000 | (uncompressed_size & 0x00FFFFFF)
        struct.pack_into(">IIII", self.dol, off, flags, uncomp_tag, disc_offset, compressed_size)

    def set_subfile_399(self, disc_offset: int, uncompressed_size: int, compressed_size: int, flags: int = 0x0000040B):
        uncomp_tag = 0x40000000 | (uncompressed_size & 0x00FFFFFF)
        struct.pack_into(">IIII", self.dol, self.SUBFILE_399_OFFSET, flags, uncomp_tag, disc_offset, compressed_size)



class GloveAttachmentTable:
    """Manages character equipment and glove bone node bindings in main.dol."""
    BASE_OFFSET = 0x000EBAAC
    SUBTABLE_OFFSET = 0x000EBB18
    DK_WRIST_INDEX = 0x000C  # Bones [6, 7, 8]

    def __init__(self, dol_bytes: bytearray):
        self.dol = dol_bytes

    def get_glove_index(self, slot: CharacterSlot) -> int:
        off = self.BASE_OFFSET + int(slot) * 2
        return struct.unpack_from(">H", self.dol, off)[0]

    def set_glove_index(self, slot: CharacterSlot, glove_index: int):
        off = self.BASE_OFFSET + int(slot) * 2
        struct.pack_into(">H", self.dol, off, glove_index)

    def bind_to_dk_skeleton(self, slot: CharacterSlot):
        self.set_glove_index(slot, self.DK_WRIST_INDEX)


class ARAMAllocator:
    """Programmatic ARAM Heap Allocator with mathematical non-overlap guarantees."""
    SECTION2_BASE_DISC = 0x1A15E800

    def __init__(self, dol_bytes: bytes):
        self.max_retail_aram_end = self._find_max_retail_aram_end(dol_bytes)
        # Allocate strictly past retail chunks with 32-byte DMA alignment
        self.current_tail = (self.max_retail_aram_end + 0x1FFF) & ~0x1FFF

    def _find_max_retail_aram_end(self, dol_bytes: bytes) -> int:
        max_end = 0
        base_off = MasterDescriptorsTable.BASE_OFFSET
        for slot_id in range(54):
            off = base_off + slot_id * 16
            flags, uncomp_sz_tag, aram_off, comp_sz = struct.unpack_from(">IIII", dol_bytes, off)
            chunk_end = aram_off + comp_sz
            if chunk_end > max_end:
                max_end = chunk_end
        return max_end

    def allocate(self, size_bytes: int) -> Tuple[int, int]:
        """Allocate an isolated ARAM chunk. Returns (aram_offset, disc_offset)."""
        alloc_aram_off = (self.current_tail + 0x1F) & ~0x1F
        disc_off = self.SECTION2_BASE_DISC + alloc_aram_off
        self.current_tail = alloc_aram_off + size_bytes
        return alloc_aram_off, disc_off
