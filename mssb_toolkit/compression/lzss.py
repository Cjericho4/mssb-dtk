"""Bit-Exact Namco LZSS Compression & Decompression Engine for GameCube (USA GYQE01).

Implements the 32-bit big-endian bitstream LZSS compression scheme used by
Namco's GameCube runtime (DecompressDiskData at 0x800A6654 / ReadBits at 0x800A673C).
"""

from __future__ import annotations

import struct
from typing import List, Optional, Tuple, Union


class BitWriter:
    """32-bit big-endian bitstream writer matching GameCube CPU ReadBits."""

    def __init__(self) -> None:
        self.words: List[int] = []
        self.cur_word: int = 0
        self.bits_in_word: int = 0

    def write_bits(self, value: int, count: int) -> None:
        """Write `count` bits from `value` into the bitstream, consumed LSB to MSB."""
        if count <= 0:
            return
        value &= (1 << count) - 1
        space_in_word = 32 - self.bits_in_word
        if count <= space_in_word:
            self.cur_word |= (value << self.bits_in_word)
            self.bits_in_word += count
            if self.bits_in_word == 32:
                self.words.append(self.cur_word)
                self.cur_word = 0
                self.bits_in_word = 0
        else:
            new_bits_needed = count - space_in_word
            high_bits = value >> new_bits_needed
            low_bits = value & ((1 << new_bits_needed) - 1)
            self.cur_word |= (high_bits << self.bits_in_word)
            self.words.append(self.cur_word)
            self.cur_word = low_bits
            self.bits_in_word = new_bits_needed

    def finish(self, align_to: int = 32) -> bytes:
        """Finish bitstream, pack to big-endian 32-bit words, and pad to alignment."""
        out = bytearray()
        if self.bits_in_word > 0:
            self.words.append(self.cur_word)
            self.cur_word = 0
            self.bits_in_word = 0
        for w in self.words:
            out.extend(w.to_bytes(4, "big"))
        if align_to > 0 and len(out) % align_to != 0:
            pad_len = align_to - (len(out) % align_to)
            out.extend(b"\x00" * pad_len)
        return bytes(out)


class BitReader:
    """32-bit big-endian bitstream reader matching GameCube CPU ReadBits (0x800A673C)."""

    def __init__(self, data: Union[bytes, bytearray]) -> None:
        self.data = bytes(data)
        self.read_offset = 0
        self.bit_buffer = 0
        self.bits_in_buffer = 0

    def read_bits(self, bit_count: int) -> int:
        """Read `bit_count` bits from the stream."""
        if bit_count <= self.bits_in_buffer:
            value = (self.bit_buffer << (32 - bit_count) & 0xFFFFFFFF) >> (32 - bit_count)
            self.bit_buffer >>= bit_count
            self.bits_in_buffer -= bit_count
            return value
        else:
            bits_needed = bit_count - self.bits_in_buffer
            value = (self.bit_buffer << bits_needed) & 0xFFFFFFFF
            if self.read_offset + 4 <= len(self.data):
                new_buffer = int.from_bytes(self.data[self.read_offset : self.read_offset + 4], "big")
                self.read_offset += 4
            else:
                new_buffer = 0

            bits_for_next = 32 - bits_needed
            value |= (new_buffer << bits_for_next & 0xFFFFFFFF) >> bits_for_next
            self.bits_in_buffer = bits_for_next
            self.bit_buffer = new_buffer >> bits_needed
            return value


class NamcoLZSSEncoder:
    """32-bit big-endian Namco LZSS bitstream compressor (11-bit lookback, 4-bit repetition)."""

    def __init__(
        self,
        lookback_bits: int = 11,
        repetition_bits: int = 4,
        max_chain_depth: int = 512,
    ) -> None:
        self.lookback_bits = lookback_bits
        self.repetition_bits = repetition_bits
        self.max_chain_depth = max_chain_depth
        self.max_lookback = 1 << lookback_bits  # 2048 bytes
        self.min_repetition = 2
        self.max_repetition = (1 << repetition_bits) - 1 + self.min_repetition  # 17 bytes

    def compress(self, data: Union[bytes, bytearray], align_32: bool = True) -> bytes:
        """Compress uncompressed byte stream into a headerless Namco LZSS bitstream.
        
        Args:
            data: Raw uncompressed bytes (e.g. .gpc model or .rel module).
            align_32: Whether to pad output to 32-byte DMA sector alignment.
            
        Returns:
            Headerless compressed byte stream.
        """
        raw = bytes(data)
        if not raw:
            return b""

        bw = BitWriter()
        pos = 0
        data_len = len(raw)
        head: dict[int, int] = {}
        prev = [0] * data_len

        while pos < data_len:
            limit = min(self.max_repetition, data_len - pos)
            best_len = 0
            best_dist = 0

            if limit >= self.min_repetition:
                win_start = max(0, pos - self.max_lookback)
                h = (raw[pos] << 8) | raw[pos + 1]
                p = head.get(h, -1)
                chain_depth = 0
                while p >= win_start and chain_depth < self.max_chain_depth:
                    l = 2
                    while l < limit and raw[p + l] == raw[pos + l]:
                        l += 1
                    if l > best_len:
                        best_len = l
                        best_dist = pos - p
                        if best_len == limit:
                            break
                    p = prev[p]
                    chain_depth += 1

            if best_len >= self.min_repetition:
                # Match repetition token: flag 0 (1 bit), distance-1 (11 bits), length-2 (4 bits)
                bw.write_bits(0, 1)
                bw.write_bits(best_dist - 1, self.lookback_bits)
                bw.write_bits(best_len - 2, self.repetition_bits)
                for i in range(best_len):
                    if pos + i + 1 < data_len:
                        h = (raw[pos + i] << 8) | raw[pos + i + 1]
                        prev[pos + i] = head.get(h, -1)
                        head[h] = pos + i
                pos += best_len
            else:
                # Literal byte: flag 1 (1 bit), byte (8 bits)
                bw.write_bits(1, 1)
                bw.write_bits(raw[pos], 8)
                if pos + 1 < data_len:
                    h = (raw[pos] << 8) | raw[pos + 1]
                    prev[pos] = head.get(h, -1)
                    head[h] = pos
                pos += 1

        return bw.finish(align_to=32 if align_32 else 0)


class ArchiveDecompressor:
    """GameCube CPU Namco LZSS decompressor matching GameCube CPU DecompressDiskData."""

    def __init__(
        self,
        buffer: Union[bytes, bytearray],
        lookback_bit_count: int = 11,
        repetition_bit_count: int = 4,
        original_size: Optional[int] = None,
    ) -> None:
        self.bytes_to_decompress = bytearray(buffer)
        self.lookback_bit_count = lookback_bit_count
        self.repetition_bit_count = repetition_bit_count
        self.original_size = original_size
        self.reader = BitReader(self.bytes_to_decompress)

    def decompress(self) -> bytearray:
        """Decompress bitstream into uncompressed bytearray."""
        if self.lookback_bit_count == 0 and self.repetition_bit_count == 0:
            if self.original_size is not None:
                return self.bytes_to_decompress[: self.original_size]
            return bytearray()

        self.reader = BitReader(self.bytes_to_decompress)
        final_data = bytearray()
        target_len = self.original_size if self.original_size is not None else float("inf")

        while len(final_data) < target_len:
            head_bit = self.reader.read_bits(1)
            if head_bit == 0:  # Repetition
                far_back = self.reader.read_bits(self.lookback_bit_count)
                repetitions = self.reader.read_bits(self.repetition_bit_count) + 2

                if far_back > len(final_data):
                    raise ValueError("Invalid data, received too far lookback")

                for _ in range(repetitions):
                    final_data.append(final_data[-1 - far_back])
            else:  # Literal
                final_data.append(self.reader.read_bits(8))

        return final_data


class GameCubeDecompressDiskDataOracle:
    """Exact emulation of GameCube DecompressDiskData (0x800A6654) and ReadBits."""

    def __init__(
        self,
        data: bytes,
        lookback_bits: int = 11,
        repetition_bits: int = 4,
        target_size: int = 0,
    ) -> None:
        self.data = data
        self.lookback_bits = lookback_bits
        self.repetition_bits = repetition_bits
        self.target_size = target_size
        self.reader = BitReader(data)
        self.error = 0
        self.out = bytearray()

    def decompress(self) -> Tuple[bytes, int]:
        bytes_to_read = self.target_size
        while bytes_to_read > 0:
            data_flag = self.reader.read_bits(1)
            if data_flag == 1:
                b = self.reader.read_bits(8)
                self.out.append(b)
                bytes_to_read -= 1
            else:
                look_back = self.reader.read_bits(self.lookback_bits) + 1
                repetition = self.reader.read_bits(self.repetition_bits) + 2
                bytes_to_read -= repetition
                if len(self.out) < look_back:
                    self.error = 1
                    break
                for _ in range(repetition):
                    self.out.append(self.out[-look_back])
        return bytes(self.out), self.error


def validate_roundtrip(raw_data: bytes, lookback_bits: int = 11, repetition_bits: int = 4) -> Tuple[bool, int, str]:
    """Validate 100% bit-exact roundtrip compression and decompression.
    
    Returns:
        (is_valid, compressed_size, error_message)
    """
    encoder = NamcoLZSSEncoder(lookback_bits, repetition_bits, max_chain_depth=512)
    compressed = encoder.compress(raw_data)
    decompressor = ArchiveDecompressor(compressed, lookback_bits, repetition_bits, len(raw_data))
    try:
        decompressed = bytes(decompressor.decompress())
    except Exception as e:
        return False, len(compressed), f"Decompression exception: {type(e).__name__} -> {e}"

    if decompressed != raw_data:
        diffs = sum(1 for a, b in zip(decompressed, raw_data) if a != b)
        return False, len(compressed), f"Byte mismatch: {diffs} differing bytes out of {len(raw_data)}"

    oracle = GameCubeDecompressDiskDataOracle(compressed, lookback_bits, repetition_bits, len(raw_data))
    oracle_out, err = oracle.decompress()
    if err != 0 or oracle_out != raw_data:
        return False, len(compressed), f"C-Oracle validation failed with error={err}"

    return True, len(compressed), ""
