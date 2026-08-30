"""Dolphin Configuration Manager for Automated Match Capture and Live Debugging."""

from __future__ import annotations

import configparser
import os
import shutil
from pathlib import Path
from typing import Optional


class DolphinConfigManager:
    """Manages Dolphin INI configuration files, texture isolation, and output directories."""

    def __init__(
        self,
        user_dir: Optional[Path] = None,
        mod_dir: Optional[Path] = None,
    ):
        self.user_dir = user_dir or Path(os.path.expanduser("~/.local/share/dolphin-emu"))
        self.config_dir = self.user_dir / "Config"
        self.gamesettings_dir = self.user_dir / "GameSettings"
        self.textures_dir = self.user_dir / "Load" / "Textures" / "GYQE01"
        self.pipes_dir = self.user_dir / "Pipes"

        self.mod_dir = mod_dir or Path("/home/michael/teamwork_projects/mssb_rio_custom_characters/4_dk_mod")
        self.mod_ini = self.mod_dir / "GameSettings" / "GYQE01.ini"
        self.mod_textures = self.mod_dir / "Load" / "Textures" / "GYQE01"

    def setup_directories(self) -> None:
        """Ensure all required Dolphin directories exist."""
        self.config_dir.mkdir(parents=True, exist_ok=True)
        self.gamesettings_dir.mkdir(parents=True, exist_ok=True)
        self.pipes_dir.mkdir(parents=True, exist_ok=True)
        (self.user_dir / "Load" / "Textures").mkdir(parents=True, exist_ok=True)

    def purge_custom_textures(self) -> None:
        """Completely remove all external PNG texture override files to enforce pure on-disc rendering."""
        target_dirs = [
            self.textures_dir,
            self.user_dir / "Load" / "Textures" / "GYQE01",
            Path(os.path.expanduser("~/.local/share/dolphin-emu/Load/Textures/GYQE01")),
            Path(os.path.expanduser("~/.config/dolphin-emu/Load/Textures/GYQE01")),
            Path(os.path.expanduser("~/.local/share/project-rio/Load/Textures/GYQE01")),
            Path(os.path.expanduser("~/.config/project-rio/Load/Textures/GYQE01")),
        ]
        for d in target_dirs:
            if d.is_symlink():
                d.unlink()
            elif d.exists():
                for f in d.glob("*.png"):
                    try:
                        f.unlink()
                    except OSError:
                        pass

    def link_custom_textures(self) -> None:
        """Link modpack HD textures (deprecated: kept only for backward compatibility if needed)."""
        if not self.mod_textures.exists():
            return

        if self.textures_dir.is_symlink():
            self.textures_dir.unlink()
        elif self.textures_dir.exists():
            shutil.rmtree(self.textures_dir)

        try:
            self.textures_dir.symlink_to(self.mod_textures)
        except OSError:
            shutil.copytree(self.mod_textures, self.textures_dir)

    def write_game_settings(self, custom_ini_content: Optional[str] = None) -> None:
        """Write GameSettings/GYQE01.ini containing Gecko cheats and lineup injection."""
        target_ini = self.gamesettings_dir / "GYQE01.ini"
        if custom_ini_content:
            target_ini.write_text(custom_ini_content)
        elif self.mod_ini.exists():
            target_ini.write_text(self.mod_ini.read_text())

    def configure_dolphin_ini(
        self,
        dump_path: Optional[Path] = None,
        backend: str = "Vulkan",
        gdb_stub: bool = True,
        gdb_port: int = 2828,
    ) -> None:
        """Write Config/Dolphin.ini with cheats enabled, frame dump path, and GDB stub configured."""
        dolphin_ini = self.config_dir / "Dolphin.ini"
        dump_str = f"DumpPath = {dump_path}\n" if dump_path else ""
        content = f"""[Core]
EnableCheats = True
GFXBackend = {backend}
CPUThread = True
Fastmem = True
DSPHLE = True
GDBStub = {str(gdb_stub)}
GDBPort = {gdb_port}

[Movie]
DumpFrames = True
DumpFramesSilent = True

[General]
{dump_str}
[Analytics]
Enabled = False
PermissionAsked = True

[AutoUpdate]
UpdateTrack = 
"""
        dolphin_ini.write_text(content)

    def configure_gdb_stub(self, port: int = 2828, enabled: bool = True) -> None:
        """Configure Dolphin GDB stub in Config/Dolphin.ini."""
        dolphin_ini = self.config_dir / "Dolphin.ini"
        cfg = configparser.ConfigParser()
        if dolphin_ini.exists():
            cfg.read(dolphin_ini)
        if not cfg.has_section("Core"):
            cfg.add_section("Core")
        cfg.set("Core", "GDBStub", str(enabled))
        cfg.set("Core", "GDBPort", str(port))
        with open(dolphin_ini, "w") as f:
            cfg.write(f)

    def configure_gfx_ini(self, backend: str = "Vulkan") -> None:
        """Write Config/GFX.ini with image dumping and strictly NO texture overrides."""
        gfx_ini = self.config_dir / "GFX.ini"
        content = f"""[Settings]
Backend = {backend}
HiresTextures = False
DumpFramesAsImages = True
DumpFormat = png
"""
        gfx_ini.write_text(content)

    def configure_gcpad_ini(self, use_pipe: bool = True) -> None:
        """Write Config/GCPadNew.ini for named pipe controller automation."""
        gcpad_ini = self.config_dir / "GCPadNew.ini"
        if use_pipe:
            content = """[GCPad1]
Device = Pipe/0/pipe0
Buttons/A = `A`
Buttons/B = `B`
Buttons/X = `X`
Buttons/Y = `Y`
Buttons/Z = `Z`
Buttons/Start = `START`
Main Stick/Up = `UP`
Main Stick/Down = `DOWN`
Main Stick/Left = `LEFT`
Main Stick/Right = `RIGHT`
Main Stick/Modifier = `SHIFT`
C-Stick/Up = `C_UP`
C-Stick/Down = `C_DOWN`
C-Stick/Left = `C_LEFT`
C-Stick/Right = `C_RIGHT`
Triggers/L = `L`
Triggers/R = `R`
D-Pad/Up = `DPAD_UP`
D-Pad/Down = `DPAD_DOWN`
D-Pad/Left = `DPAD_LEFT`
D-Pad/Right = `DPAD_RIGHT`
[GCPad2]
Device = XInput2/0/Virtual core pointer
[GCPad3]
Device = XInput2/0/Virtual core pointer
[GCPad4]
Device = XInput2/0/Virtual core pointer
"""
        else:
            content = """[GCPad1]
Device = XInput2/0/Virtual core pointer
Buttons/A = `X`
Buttons/B = `Z`
Buttons/Start = `Return`
"""
        gcpad_ini.write_text(content)

    def prepare_all(
        self,
        dump_path: Optional[Path] = None,
        backend: str = "Vulkan",
        gdb_stub: bool = True,
        gdb_port: int = 2828,
        use_pipe: bool = True,
    ) -> None:
        """Execute complete setup of Dolphin configuration."""
        self.setup_directories()
        self.purge_custom_textures()
        self.write_game_settings()
        self.configure_dolphin_ini(
            dump_path=dump_path,
            backend=backend,
            gdb_stub=gdb_stub,
            gdb_port=gdb_port,
        )
        self.configure_gfx_ini(backend=backend)
        self.configure_gcpad_ini(use_pipe=use_pipe)
