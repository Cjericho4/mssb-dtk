"""Frame Harvester Subsystem for Dolphin Live Match Capture."""

from __future__ import annotations

import shutil
import time
from pathlib import Path
from typing import List, Optional


class FrameHarvester:
    """Monitors and harvests rendered PNG frames from Dolphin frame dump directory."""

    def __init__(self, dump_dir: Path, output_dir: Optional[Path] = None):
        self.dump_dir = Path(dump_dir)
        self.output_dir = Path(output_dir) if output_dir else self.dump_dir

    def ensure_directories(self) -> None:
        self.dump_dir.mkdir(parents=True, exist_ok=True)
        self.output_dir.mkdir(parents=True, exist_ok=True)

    def clear_dump_dir(self) -> None:
        """Purge old frames from dump directory prior to new match run."""
        if self.dump_dir.exists():
            for p in self.dump_dir.glob("*.png"):
                try:
                    p.unlink()
                except OSError:
                    pass

    def get_captured_frames(self) -> List[Path]:
        """Return sorted list of captured PNG frames."""
        if not self.dump_dir.exists():
            return []
        return sorted(list(self.dump_dir.glob("*.png")))

    def wait_for_frames(self, min_count: int = 13, timeout: float = 30.0) -> List[Path]:
        """Poll dump directory until min_count frames are written or timeout expires."""
        start = time.time()
        while time.time() - start < timeout:
            frames = self.get_captured_frames()
            if len(frames) >= min_count:
                return frames
            time.sleep(0.5)
        return self.get_captured_frames()

    def harvest_to_output(self, min_count: int = 13, timeout: float = 30.0) -> List[Path]:
        """Collect frames and copy to destination output directory."""
        frames = self.wait_for_frames(min_count=min_count, timeout=timeout)
        self.output_dir.mkdir(parents=True, exist_ok=True)
        copied = []
        for f in frames:
            dest = self.output_dir / f.name
            if f != dest:
                shutil.copy2(f, dest)
            copied.append(dest)
        return copied
