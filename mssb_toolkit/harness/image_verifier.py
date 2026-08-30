"""Automated Image Verification Subsystem with Computer Vision Quality Metrics."""

import configparser
import math
import os
from pathlib import Path
from typing import Dict, List, Optional, Tuple
from PIL import Image
import numpy as np


class ImageVerifier:
    """Verifies captured screenshot integrity, resolution, entropy, and diamond visual presence."""

    MIN_COUNT = 13
    EXPECTED_SIZE = (640, 480)
    MIN_GRASS_FRACTION = 0.05
    MIN_DIRT_FRACTION = 0.05
    MIN_GORILLA_FRACTION = 0.01
    MAX_MARIO_RED_CENTER_COUNT = 500.0
    MIN_AVERAGE_STD = 25.0
    MIN_SHANNON_ENTROPY = 5.0

    def __init__(self, screenshots_dir: Path):
        self.screenshots_dir = screenshots_dir

    def get_screenshots(self) -> List[Path]:
        """Get sorted list of all PNG images in screenshots directory."""
        if not self.screenshots_dir.exists():
            return []
        return sorted(list(self.screenshots_dir.glob("*.png")))

    def verify_count(self) -> Tuple[bool, str]:
        """Assert screenshot directory contains at least the minimum required count."""
        images = self.get_screenshots()
        if len(images) < self.MIN_COUNT:
            return False, f"Expected at least {self.MIN_COUNT} screenshots, found {len(images)}"
        return True, f"Found {len(images)} screenshots (>= {self.MIN_COUNT})"

    def verify_png_headers(self) -> Tuple[bool, str]:
        """Verify all files have valid 8-byte PNG binary signatures."""
        for p in self.get_screenshots():
            with open(p, "rb") as f:
                sig = f.read(8)
                if sig != b"\x89PNG\r\n\x1a\n":
                    return False, f"{p.name} lacks valid 8-byte PNG signature"
        return True, "All screenshots possess valid PNG signatures"

    def verify_resolution_and_format(self) -> Tuple[bool, str]:
        """Verify image format, resolution, and color modes."""
        for p in self.get_screenshots():
            with Image.open(p) as img:
                if img.format != "PNG":
                    return False, f"{p.name} format is {img.format}, expected PNG"
                if img.size != self.EXPECTED_SIZE:
                    if img.size[0] < 608 or img.size[1] < 448:
                        return False, f"{p.name} size {img.size} below minimum GameCube resolution"
                if img.mode not in ["RGB", "RGBA"]:
                    return False, f"{p.name} mode {img.mode} not RGB or RGBA"
        return True, f"All screenshots meet resolution {self.EXPECTED_SIZE} and mode constraints"

    def verify_entropy_and_variance(self) -> Tuple[bool, str]:
        """Verify images have high Shannon entropy and color standard deviation."""
        for p in self.get_screenshots():
            with Image.open(p) as img:
                arr = np.array(img.convert("RGB"))
                
                std_r = float(np.std(arr[:, :, 0]))
                std_g = float(np.std(arr[:, :, 1]))
                std_b = float(np.std(arr[:, :, 2]))
                avg_std = (std_r + std_g + std_b) / 3.0
                if avg_std < self.MIN_AVERAGE_STD:
                    return False, f"{p.name} average std {avg_std:.2f} < {self.MIN_AVERAGE_STD} (flat/blank image)"

                gray = np.dot(arr[..., :3], [0.2989, 0.5870, 0.1140]).astype(np.uint8)
                hist, _ = np.histogram(gray, bins=256, range=(0, 256), density=True)
                hist = hist[hist > 0]
                entropy = -float(np.sum(hist * np.log2(hist)))
                if entropy < self.MIN_SHANNON_ENTROPY:
                    return False, f"{p.name} Shannon entropy {entropy:.2f} < {self.MIN_SHANNON_ENTROPY}"

        return True, "All screenshots exceed entropy and color variance thresholds"

    def verify_diamond_and_character_features(self) -> Tuple[bool, str]:
        """Verify presence of outfield grass, infield dirt, gorilla character palette, and anti-attract rejection."""
        for p in self.get_screenshots():
            with Image.open(p) as img:
                arr = np.array(img.convert("RGB"))
                h, w, _ = arr.shape
                total_pixels = float(h * w)

                grass_mask = (arr[:, :, 1] > arr[:, :, 0] + 15) & (arr[:, :, 1] > arr[:, :, 2] + 15)
                grass_fraction = float(np.sum(grass_mask)) / total_pixels
                if grass_fraction < self.MIN_GRASS_FRACTION:
                    return False, f"{p.name} grass fraction {grass_fraction:.3f} < {self.MIN_GRASS_FRACTION}"

                dirt_mask = (arr[:, :, 0] > 100) & (arr[:, :, 1] > 60) & (arr[:, :, 0] > arr[:, :, 2] + 25)
                dirt_fraction = float(np.sum(dirt_mask)) / total_pixels
                if dirt_fraction < self.MIN_DIRT_FRACTION:
                    return False, f"{p.name} dirt fraction {dirt_fraction:.3f} < {self.MIN_DIRT_FRACTION}"

                gorilla_mask = (
                    (arr[:, :, 0] >= 40)
                    & (arr[:, :, 0] <= 130)
                    & (arr[:, :, 1] >= 25)
                    & (arr[:, :, 1] <= 90)
                    & (arr[:, :, 2] < 65)
                    & (arr[:, :, 0] > arr[:, :, 1])
                )
                blue_char_mask = (
                    (arr[:, :, 2] > 100)
                    & (arr[:, :, 2] > arr[:, :, 0] + 20)
                    & (arr[:, :, 2] > arr[:, :, 1] + 10)
                )
                combined_char = gorilla_mask | blue_char_mask
                gorilla_fraction = float(np.sum(combined_char)) / total_pixels
                if gorilla_fraction < self.MIN_GORILLA_FRACTION:
                    return False, f"{p.name} character palette fraction {gorilla_fraction:.3f} < {self.MIN_GORILLA_FRACTION}"

                center_box = arr[int(h * 0.3):int(h * 0.7), int(w * 0.3):int(w * 0.7)]
                mario_red = (center_box[:, :, 0] > 140) & (center_box[:, :, 1] < 70) & (center_box[:, :, 2] < 70)
                mario_red_count = float(np.sum(mario_red))
                if mario_red_count > self.MAX_MARIO_RED_CENTER_COUNT:
                    return False, f"{p.name} failed anti-title rejection: center red count {mario_red_count} > {self.MAX_MARIO_RED_CENTER_COUNT}"

        return True, "All screenshots satisfy diamond CV features, gorilla palette, and anti-attract rejection"

    def verify_no_texture_overrides(self) -> Tuple[bool, str]:
        """Verify that NO external PNG texture override files exist in Dolphin or Project Rio directories."""
        dirs_to_check = [
            Path(os.path.expanduser("~/.local/share/dolphin-emu/Load/Textures/GYQE01")),
            Path(os.path.expanduser("~/.local/share/project-rio/Load/Textures/GYQE01")),
            Path(os.path.expanduser("~/.config/dolphin-emu/Load/Textures/GYQE01")),
            Path(os.path.expanduser("~/.config/project-rio/Load/Textures/GYQE01")),
        ]
        for d in dirs_to_check:
            if d.exists():
                pngs = list(d.glob("*.png"))
                if len(pngs) > 0:
                    return False, f"Texture override files found in {d}: {[p.name for p in pngs]}"

        gfx_paths = [
            Path(os.path.expanduser("~/.local/share/dolphin-emu/Config/GFX.ini")),
            Path(os.path.expanduser("~/.config/dolphin-emu/Config/GFX.ini")),
        ]
        for gp in gfx_paths:
            if gp.exists():
                cfg = configparser.ConfigParser()
                cfg.read(gp)
                hires = cfg.get("Settings", "HiresTextures", fallback="False")
                if hires.lower() == "true":
                    return False, f"GFX.ini at {gp} has HiresTextures = True (must be False for standalone rendering)"

        return True, "Verified 0 texture override files exist and HiresTextures = False"

    def run_all_verifications(self) -> Dict[str, Tuple[bool, str]]:
        """Run all verification passes and return results dict."""
        return {
            "count": self.verify_count(),
            "png_headers": self.verify_png_headers(),
            "resolution_format": self.verify_resolution_and_format(),
            "entropy_variance": self.verify_entropy_and_variance(),
            "diamond_features": self.verify_diamond_and_character_features(),
            "texture_overrides_purged": self.verify_no_texture_overrides(),
        }
