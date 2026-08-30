"""Native GameCube GX Hardware CMPR (DXT1) Texture Encoder and Container Injector.

Implements:
- RGB to RGB565 color quantization.
- 4x4 DXT1 sub-block encoding with optimal endpoint selection and 4-level quantization.
- 8x8 GameCube macro-tile Z-ordering.
- Fast solid color pattern generators for test patterns (Pure Red 0xF800, Pure Blue 0x001F, etc.).
- Complete native CMPR texture injection into uncompressed .gpc model containers across all 10 texture offsets.
- Zero Zone B geometry modifications (< 0x000180 and >= 0x004F00 remain 100% bit-exact).
"""

from __future__ import annotations

import struct
from typing import Dict, List, Optional, Tuple, Union
from PIL import Image
import numpy as np


# Standard RGB565 Colors
COLOR_PURE_RED = 0xF800      # RGB(255, 0, 0)
COLOR_PURE_GREEN = 0x07E0    # RGB(0, 255, 0)
COLOR_PURE_BLUE = 0x001F     # RGB(0, 0, 255)
COLOR_PURE_YELLOW = 0xFFE0   # RGB(255, 255, 0)
COLOR_VIBRANT_CYAN = 0x05BF  # RGB(0, 180, 255)
COLOR_BRIGHT_PURPLE = 0xF81F # RGB(255, 0, 255)
COLOR_WHITE = 0xFFFF
COLOR_BLACK = 0x0000

# Container Size
GPC_CONTAINER_SIZE = 119736    # 0x1D3B8 bytes (donkey00.gpc)
GPC_EQUIPMENT_SIZE = 60896     # 0x0EE40 bytes (donkey01.gpc)

# Exact 10 Texture Offsets in TextureArchiveHeader at offset 0x20 of donkey00.gpc / donkey01.gpc
# Entire texture region contiguously spans 0x000180 .. 0x004F00 (19,840 bytes).
DK_TEXTURE_OFFSETS_V5: Dict[int, Dict[str, Union[int, str]]] = {
    9: {"offset": 0x000180, "size": 512,  "width": 32,  "height": 32, "desc": "Aux Detail 1"},
    4: {"offset": 0x000380, "size": 512,  "width": 32,  "height": 32, "desc": "Aux Detail 2"},
    8: {"offset": 0x000580, "size": 8192, "width": 128, "height": 128, "desc": "Primary Body Fur"},
    7: {"offset": 0x002580, "size": 2048, "width": 64,  "height": 64, "desc": "Face Fur"},
    6: {"offset": 0x002D80, "size": 2048, "width": 64,  "height": 64, "desc": "Limbs Fur"},
    3: {"offset": 0x003580, "size": 2048, "width": 64,  "height": 64, "desc": "Hands/Feet Fur"},
    2: {"offset": 0x003D80, "size": 2048, "width": 64,  "height": 64, "desc": "Eyes/Tie"},
    5: {"offset": 0x004580, "size": 2048, "width": 64,  "height": 64, "desc": "Shading/Aux Fur"},
    1: {"offset": 0x004D80, "size": 128,  "width": 16,  "height": 16, "desc": "Aux Detail 3"},
    0: {"offset": 0x004E00, "size": 256,  "width": 32,  "height": 16, "desc": "Aux Detail 4 / Teeth"},
}

# Texture Region Boundaries
DK_TEXTURE_REGION_START = 0x000180
DK_TEXTURE_REGION_END = 0x004F00
DK_TEXTURE_REGION_SIZE = DK_TEXTURE_REGION_END - DK_TEXTURE_REGION_START  # 19,840 bytes

# Primary Texture Offsets for backward compatibility
OFF_PRIMARY_64 = 0x002580      # 2,048 bytes (64x64 Face & Fur)
OFF_PRIMARY_128 = 0x002D80     # 8,192 bytes (128x128 Primary Body)
OFF_LIMBS_64 = 0x002D80        # Tex 6: 2,048 bytes (64x64 Limbs Fur)
OFF_HANDS_64 = 0x003580        # Tex 3: 2,048 bytes (64x64 Hands/Feet Fur)
OFF_EYES_TIE_64 = 0x003D80     # Tex 2: 2,048 bytes (64x64 Eyes/Tie)
OFF_SHADING_64 = 0x004580      # Tex 5: 2,048 bytes (64x64 Shading/Aux Fur)
OFF_AUX_32_1 = 0x000180        # Tex 9: 512 bytes (32x32 Aux Detail 1)
OFF_AUX_32_2 = 0x000380        # Tex 4: 512 bytes (32x32 Aux Detail 2)
OFF_AUX_16 = 0x004D80          # Tex 1: 128 bytes (16x16 Aux Detail 3)
OFF_AUX_TEETH = 0x004E00       # Tex 0: 256 bytes (32x16 Aux Detail 4 / Teeth)

# Legacy offsets (for documentation / legacy aliases)
OFF_AUX_64 = 0x019640          # 2,048 bytes (64x64 Auxiliary Fur)
OFF_AUX_128 = 0x01A660         # 8,192 bytes (128x128 Auxiliary Body & Limbs)
OFF_MIPMAP_32 = 0x1D0E0
OFF_MIPMAP_16 = 0x1D100
OFF_MIPMAP_8 = 0x1D120


def rgb_to_rgb565(r: int, g: int, b: int) -> int:
    """Convert 8-bit RGB components to 16-bit Big-Endian RGB565."""
    r5 = (r >> 3) & 0x1F
    g6 = (g >> 2) & 0x3F
    b5 = (b >> 3) & 0x1F
    return (r5 << 11) | (g6 << 5) | b5


def rgb565_to_rgb(c: int) -> Tuple[int, int, int]:
    """Convert 16-bit RGB565 to 8-bit (R, G, B) tuple."""
    r5 = (c >> 11) & 0x1F
    g6 = (c >> 5) & 0x3F
    b5 = c & 0x1F
    r8 = (r5 * 527 + 23) >> 6
    g8 = (g6 * 259 + 33) >> 6
    b8 = (b5 * 527 + 23) >> 6
    return r8, g8, b8


class CMPREncoder:
    """Encodes raw RGB images and color patterns into GameCube GX CMPR (DXT1) format."""

    @classmethod
    def generate_solid_block(cls, rgb565_color: int) -> bytes:
        """Generate a single 8-byte 4x4 sub-block of a solid RGB565 color."""
        return struct.pack(">HHI", rgb565_color, 0x0000, 0x00000000)

    @classmethod
    def generate_solid_cmpr(cls, width: int, height: int, rgb565_color: int) -> bytes:
        """Generate a full CMPR texture payload of uniform solid color.
        
        Args:
            width: Texture width (must be multiple of 8 or 4 for sub-blocks).
            height: Texture height (must be multiple of 8 or 4 for sub-blocks).
            rgb565_color: 16-bit RGB565 color.
            
        Returns:
            Raw CMPR byte payload ((width * height) // 2 bytes).
        """
        assert (width * height) % 16 == 0, f"Dimensions ({width}x{height}) must be divisible by 16 pixels"
        total_subblocks = (width * height) // 16
        single_subblock = cls.generate_solid_block(rgb565_color)
        return single_subblock * total_subblocks

    @classmethod
    def encode_subblock(cls, pixels_4x4: np.ndarray) -> bytes:
        """Encode a 4x4 RGB pixel block into 8 CMPR bytes."""
        pixels_flat = pixels_4x4.reshape(-1, 3)
        if np.all(pixels_flat == pixels_flat[0]):
            r, g, b = pixels_flat[0]
            c565 = rgb_to_rgb565(int(r), int(g), int(b))
            return cls.generate_solid_block(c565)

        lum = 0.299 * pixels_flat[:, 0] + 0.587 * pixels_flat[:, 1] + 0.114 * pixels_flat[:, 2]
        idx_max = int(np.argmax(lum))
        idx_min = int(np.argmin(lum))

        c0 = rgb_to_rgb565(int(pixels_flat[idx_max, 0]), int(pixels_flat[idx_max, 1]), int(pixels_flat[idx_max, 2]))
        c1 = rgb_to_rgb565(int(pixels_flat[idx_min, 0]), int(pixels_flat[idx_min, 1]), int(pixels_flat[idx_min, 2]))

        if c0 <= c1:
            c0, c1 = c1, c0
            c0_rgb, c1_rgb = pixels_flat[idx_min], pixels_flat[idx_max]
        else:
            c0_rgb, c1_rgb = pixels_flat[idx_max], pixels_flat[idx_min]

        c0_arr = np.array(rgb565_to_rgb(c0), dtype=float)
        c1_arr = np.array(rgb565_to_rgb(c1), dtype=float)
        c2_arr = (2.0 * c0_arr + c1_arr) / 3.0
        c3_arr = (c0_arr + 2.0 * c1_arr) / 3.0
        palette = np.stack([c0_arr, c1_arr, c2_arr, c3_arr])

        diffs = pixels_flat[:, np.newaxis, :] - palette[np.newaxis, :, :]
        dist_sq = np.sum(diffs**2, axis=2)
        best_indices = np.argmin(dist_sq, axis=1)

        packed_bits = 0
        for idx in best_indices:
            packed_bits = (packed_bits << 2) | (int(idx) & 0x3)

        return struct.pack(">HHI", c0, c1, packed_bits)

    @classmethod
    def encode_image(cls, img: Union[Image.Image, np.ndarray]) -> bytes:
        """Encode PIL Image or numpy RGB array into full CMPR payload."""
        if isinstance(img, Image.Image):
            arr = np.array(img.convert("RGB"))
        else:
            arr = img

        h, w, _ = arr.shape
        assert (w * h) % 16 == 0, f"Image dimensions ({w}x{h}) must contain integer 4x4 sub-blocks"

        out = bytearray()
        # Macro-tile 8x8 with 4x4 sub-blocks
        for ty in range(0, h, 8):
            for tx in range(0, w, 8):
                sb0 = arr[ty : ty + 4, tx : tx + 4]
                sb1 = arr[ty : ty + 4, tx + 4 : tx + 8] if (tx + 4 < w) else np.zeros((4, 4, 3), dtype=np.uint8)
                sb2 = arr[ty + 4 : ty + 8, tx : tx + 4] if (ty + 4 < h) else np.zeros((4, 4, 3), dtype=np.uint8)
                sb3 = arr[ty + 4 : ty + 8, tx + 4 : tx + 8] if (ty + 4 < h and tx + 4 < w) else np.zeros((4, 4, 3), dtype=np.uint8)

                out.extend(cls.encode_subblock(sb0))
                if tx + 4 < w:
                    out.extend(cls.encode_subblock(sb1))
                if ty + 4 < h:
                    out.extend(cls.encode_subblock(sb2))
                if ty + 4 < h and tx + 4 < w:
                    out.extend(cls.encode_subblock(sb3))

        return bytes(out)


def inject_all_10_textures(
    base_gpc_bytes: Union[bytes, bytearray],
    texture_payloads: Dict[int, bytes],
) -> bytearray:
    """Inject CMPR textures into exact 10 offsets spanning 0x000180..0x004F00 with 0 Zone B modifications.
    
    Args:
        base_gpc_bytes: Uncompressed .gpc model container bytes.
        texture_payloads: Mapping from texture index (0..9) to raw CMPR payload bytes.
        
    Returns:
        Modified uncompressed .gpc model container with zero geometry corruption.
    """
    model = bytearray(base_gpc_bytes)
    if len(model) < DK_TEXTURE_REGION_END:
        raise ValueError(f"Model container too small for texture injection: {len(model)} bytes (minimum {DK_TEXTURE_REGION_END})")

    for tex_id, payload in texture_payloads.items():
        if tex_id not in DK_TEXTURE_OFFSETS_V5:
            raise KeyError(f"Invalid texture index {tex_id}. Valid indices: 0..9")
        info = DK_TEXTURE_OFFSETS_V5[tex_id]
        expected_size = int(info["size"])
        if len(payload) != expected_size:
            raise ValueError(
                f"Tex {tex_id} ({info['desc']}) expected {expected_size} bytes, got {len(payload)} bytes"
            )
        off = int(info["offset"])
        model[off : off + expected_size] = payload

    # Safety assertions: Verify header (< 0x000180) and structures past 0x004F00 (Zone B geometry >= 0x015BE0) remain untouched
    assert model[:DK_TEXTURE_REGION_START] == base_gpc_bytes[:DK_TEXTURE_REGION_START], (
        f"Safety error: modified header before 0x{DK_TEXTURE_REGION_START:06X}"
    )
    if len(base_gpc_bytes) >= DK_TEXTURE_REGION_END:
        assert model[DK_TEXTURE_REGION_END:] == base_gpc_bytes[DK_TEXTURE_REGION_END:], (
            f"Safety error: modified data structures after 0x{DK_TEXTURE_REGION_END:06X}"
        )

    return model


def create_v5_recolored_model(
    base_gpc_bytes: Union[bytes, bytearray],
    primary_color: int,
    aux_colors: Optional[Dict[int, int]] = None,
) -> bytearray:
    """Create a complete .gpc model container with custom CMPR colors across all 10 texture offsets.
    
    Args:
        base_gpc_bytes: Uncompressed .gpc model container (119,736 B or 60,896 B).
        primary_color: 16-bit RGB565 color for primary fur/body (e.g. 0x001F for Pure Blue).
        aux_colors: Optional mapping from texture index (0..9) to 16-bit RGB565 override color.
        
    Returns:
        Modified uncompressed .gpc model container with zero Zone B geometry modifications.
    """
    aux_colors = aux_colors or {}
    texture_payloads: Dict[int, bytes] = {}

    for tex_id, info in DK_TEXTURE_OFFSETS_V5.items():
        w = int(info["width"])
        h = int(info["height"])
        color = aux_colors.get(tex_id, primary_color)
        payload = CMPREncoder.generate_solid_cmpr(w, h, color)
        texture_payloads[tex_id] = payload

    return inject_all_10_textures(base_gpc_bytes, texture_payloads)


def decode_cmpr_to_image(data: bytes, width: int, height: int) -> Image.Image:
    """Decode raw GameCube GX CMPR (DXT1) byte payload into RGB PIL Image."""
    img = np.zeros((height, width, 3), dtype=np.uint8)
    offset = 0
    for by in range(0, height, 8):
        for bx in range(0, width, 8):
            for sy, sx in [(0, 0), (0, 4), (4, 0), (4, 4)]:
                c0_raw, c1_raw, bits = struct.unpack_from(">HHI", data, offset)
                offset += 8
                r0, g0, b0 = rgb565_to_rgb(c0_raw)
                r1, g1, b1 = rgb565_to_rgb(c1_raw)

                if c0_raw > c1_raw:
                    pal = [
                        (r0, g0, b0),
                        (r1, g1, b1),
                        ((2 * r0 + r1) // 3, (2 * g0 + g1) // 3, (2 * b0 + b1) // 3),
                        ((r0 + 2 * r1) // 3, (g0 + 2 * g1) // 3, (b0 + 2 * b1) // 3),
                    ]
                else:
                    pal = [
                        (r0, g0, b0),
                        (r1, g1, b1),
                        ((r0 + r1) // 2, (g0 + g1) // 2, (b0 + b1) // 2),
                        (0, 0, 0),
                    ]
                for py in range(4):
                    for px in range(4):
                        idx = (py * 4) + px
                        shift = (15 - idx) * 2
                        code = (bits >> shift) & 0x3
                        y = by + sy + py
                        x = bx + sx + px
                        if y < height and x < width:
                            img[y, x] = pal[code]
    return Image.fromarray(img)


def tint_fur_to_blue(img: Image.Image, is_fur_texture: bool = True, target_hue: float = 0.60) -> Image.Image:
    """Shift brown/tan fur tones into rich vibrant blue while preserving lighting, teeth, eyes, and red tie."""
    import colorsys
    arr = np.array(img.convert("RGB"), dtype=np.float32) / 255.0
    h_out, w_out, _ = arr.shape
    out = np.zeros_like(arr)

    for y in range(h_out):
        for x in range(w_out):
            r, g, b = arr[y, x]
            h, s, v = colorsys.rgb_to_hsv(r, g, b)

            # Identify brown / golden / tan fur tones (H in 0.01..0.16)
            is_brown_fur = (0.01 <= h <= 0.16) and (s > 0.18) and (v > 0.05)
            # Dark brown shadow
            is_dark_fur = (0.00 <= h <= 0.18) and (s > 0.10) and (0.03 <= v <= 0.40)

            if is_fur_texture and (is_brown_fur or is_dark_fur):
                # Shift to vibrant cool blue (Hue ~ 0.58..0.62)
                new_h = target_hue + (h - 0.08) * 0.4
                new_s = min(1.0, max(0.40, s * 1.15))
                new_r, new_g, new_b = colorsys.hsv_to_rgb(new_h, new_s, v)
                out[y, x] = [new_r, new_g, new_b]
            else:
                # Leave skin, tie, teeth, eyes, and neutral pixels 100% original
                out[y, x] = [r, g, b]

    return Image.fromarray((out * 255.0).astype(np.uint8))


def tint_color_565(c: int, target_hue: float = 0.60) -> int:
    """Shift 16-bit RGB565 color from brown/tan to vibrant blue while preserving brightness."""
    import colorsys
    if c == 0:
        return 0
    r8, g8, b8 = rgb565_to_rgb(c)
    h, s, v = colorsys.rgb_to_hsv(r8 / 255.0, g8 / 255.0, b8 / 255.0)

    # Identify brown / golden / tan fur tones (H in 0.01..0.16)
    is_brown = (0.01 <= h <= 0.16) and (s > 0.15) and (v > 0.05)
    is_dark_brown = (0.00 <= h <= 0.18) and (s > 0.10) and (0.03 <= v <= 0.40)

    if is_brown or is_dark_brown:
        new_h = target_hue + (h - 0.08) * 0.4
        new_s = min(1.0, max(0.50, s * 1.2))
        nr, ng, nb = colorsys.hsv_to_rgb(new_h, new_s, v)
        r5 = max(0, min(31, int(round(nr * 31.0))))
        g6 = max(0, min(63, int(round(ng * 63.0))))
        b5 = max(0, min(31, int(round(nb * 31.0))))
        return (r5 << 11) | (g6 << 5) | b5
    return c


def create_inplace_tinted_model(
    base_gpc_bytes: Union[bytes, bytearray],
    target_hue: float = 0.60,
) -> bytearray:
    """Tint brown fur to blue by modifying RGB565 endpoints directly inside CMPR blocks, preserving 100% of index streams."""
    model = bytearray(base_gpc_bytes)

    for tex_id, info in DK_TEXTURE_OFFSETS_V5.items():
        off = int(info["offset"])
        sz = int(info["size"])
        for b_off in range(off, off + sz, 8):
            c0, c1, idx = struct.unpack_from(">HHI", model, b_off)
            new_c0 = tint_color_565(c0, target_hue=target_hue)
            new_c1 = tint_color_565(c1, target_hue=target_hue)

            # Preserve c0 > c1 4-color vs 3-color relationship
            if c0 > c1 and new_c0 <= new_c1:
                if new_c0 > 0:
                    new_c1 = max(0, new_c0 - 1)
                else:
                    new_c0 = new_c1 + 1
            elif c0 <= c1 and new_c0 > new_c1:
                new_c0, new_c1 = new_c1, new_c0

            struct.pack_into(">HHI", model, b_off, new_c0, new_c1, idx)

    # Verify Zone B and header remain bit-exact
    assert model[:DK_TEXTURE_REGION_START] == base_gpc_bytes[:DK_TEXTURE_REGION_START]
    assert model[DK_TEXTURE_REGION_END:] == base_gpc_bytes[DK_TEXTURE_REGION_END:]

    return model


create_tinted_fur_model = create_inplace_tinted_model


class CMPRModelInjector:
    """Injects native CMPR textures directly into uncompressed MSSB .gpc model containers."""

    inject_all_10_textures = staticmethod(inject_all_10_textures)
    create_v5_recolored_model = staticmethod(create_v5_recolored_model)
    create_tinted_fur_model = staticmethod(create_inplace_tinted_model)
    create_inplace_tinted_model = staticmethod(create_inplace_tinted_model)
    decode_cmpr_to_image = staticmethod(decode_cmpr_to_image)
    tint_fur_to_blue = staticmethod(tint_fur_to_blue)
    tint_color_565 = staticmethod(tint_color_565)

    @classmethod
    def inject_native_cmpr_model(
        cls,
        base_gpc_bytes: bytes,
        primary_64_cmpr: bytes,
        primary_128_cmpr: bytes,
        aux_64_cmpr: Optional[bytes] = None,
        aux_128_cmpr: Optional[bytes] = None,
    ) -> bytearray:
        """Inject CMPR texture payloads across all fur/body offsets with 0 Zone B geometry writes.
        
        Args:
            base_gpc_bytes: Uncompressed .gpc model container.
            primary_64_cmpr: 2,048-byte 64x64 CMPR payload (0x002580).
            primary_128_cmpr: 8,192-byte 128x128 CMPR payload (0x000580).
            aux_64_cmpr: Optional auxiliary 64x64 CMPR payload (0x002D80).
            aux_128_cmpr: Optional auxiliary 128x128 CMPR payload.
            
        Returns:
            Modified uncompressed .gpc model container with zero geometry corruption.
        """
        if len(primary_64_cmpr) != 2048:
            raise ValueError(f"Primary 64x64 CMPR must be 2,048 bytes, got {len(primary_64_cmpr)}")
        if len(primary_128_cmpr) != 8192:
            raise ValueError(f"Primary 128x128 CMPR must be 8,192 bytes, got {len(primary_128_cmpr)}")

        aux_64 = aux_64_cmpr if aux_64_cmpr is not None else primary_64_cmpr

        texture_payloads = {
            8: primary_128_cmpr,
            7: primary_64_cmpr,
            6: aux_64,
            3: primary_64_cmpr,
            5: primary_64_cmpr,
        }

        model = bytearray(base_gpc_bytes)
        for tex_id, payload in texture_payloads.items():
            info = DK_TEXTURE_OFFSETS_V5[tex_id]
            off = int(info["offset"])
            sz = int(info["size"])
            model[off : off + sz] = payload

        # Assert no corruption outside 0x000180..0x004F00
        assert model[:DK_TEXTURE_REGION_START] == base_gpc_bytes[:DK_TEXTURE_REGION_START]
        assert model[DK_TEXTURE_REGION_END:] == base_gpc_bytes[DK_TEXTURE_REGION_END:]

        return model

    @classmethod
    def create_solid_color_model(
        cls,
        base_gpc_bytes: bytes,
        rgb565_color: int,
    ) -> bytearray:
        """Create a complete .gpc model with solid CMPR color textures strictly in 0x000180..0x004F00.
        
        Args:
            base_gpc_bytes: Uncompressed .gpc model container (119,736 B or 60,896 B).
            rgb565_color: 16-bit Big-Endian RGB565 color (e.g. 0x001F for Pure Blue).
            
        Returns:
            Modified uncompressed .gpc model container with 100% solid color fur and preserved Zone B geometry.
        """
        return create_v5_recolored_model(base_gpc_bytes, rgb565_color)
