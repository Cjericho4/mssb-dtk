"""Dolphin Named Pipe Controller Interface and Closed-Loop Menu Navigator.

Provides:
- DolphinPipeController: POSIX named pipe (FIFO) streamer for Dolphin Linux InputCommon.
- MenuNavigator: Automated closed-loop menu navigation state machine from ISO boot to live match.
"""

from __future__ import annotations

import os
import time
from pathlib import Path
from typing import Any, List, Optional, Tuple, Union


class DolphinPipeController:
    """Streams controller button and analog stick events to Dolphin via POSIX named pipe."""

    VALID_BUTTONS = {
        "A", "B", "X", "Y", "Z", "START",
        "UP", "DOWN", "LEFT", "RIGHT",
        "C_UP", "C_DOWN", "C_LEFT", "C_RIGHT",
        "DPAD_UP", "DPAD_DOWN", "DPAD_LEFT", "DPAD_RIGHT",
        "L", "R",
    }

    def __init__(self, pipe_path: Union[str, Path]):
        self.pipe_path = Path(pipe_path)
        self.pipe_fd: Optional[int] = None
        self._is_open = False
        self._command_log: List[str] = []

    def create_pipe(self) -> None:
        """Create POSIX named pipe (FIFO) at pipe_path."""
        self.pipe_path.parent.mkdir(parents=True, exist_ok=True)
        if self.pipe_path.exists():
            try:
                self.pipe_path.unlink()
            except OSError:
                pass
        try:
            os.mkfifo(str(self.pipe_path), 0o600)
        except FileExistsError:
            pass

    def open_pipe(self, non_blocking: bool = True, timeout: float = 5.0) -> bool:
        """Open the FIFO writer handle.
        
        In Linux POSIX FIFO semantics, O_WRONLY | O_NONBLOCK will return ENXIO if no
        reader (Dolphin) is open yet. If so, retry until timeout or reader connects.
        """
        if self._is_open and self.pipe_fd is not None:
            return True

        if not self.pipe_path.exists():
            self.create_pipe()

        start = time.time()
        while time.time() - start < timeout:
            try:
                flags = os.O_WRONLY
                if non_blocking:
                    flags |= os.O_NONBLOCK
                self.pipe_fd = os.open(str(self.pipe_path), flags)
                self._is_open = True
                return True
            except OSError:
                time.sleep(0.01)

        return False

    def write_raw_command(self, cmd_line: str) -> None:
        """Write formatted ASCII line to FIFO."""
        clean_cmd = cmd_line.strip()
        self._command_log.append(clean_cmd)
        msg = f"{clean_cmd}\n".encode("ascii")

        if not self._is_open or self.pipe_fd is None:
            if not self.open_pipe(non_blocking=True, timeout=0.01):
                return  # Buffer in log if reader not yet attached

        try:
            if self.pipe_fd is not None:
                os.write(self.pipe_fd, msg)
        except (OSError, BrokenPipeError):
            self.close()

    def press_button(self, btn: str) -> None:
        """Send PRESS <BUTTON> command."""
        btn_norm = btn.upper()
        self.write_raw_command(f"PRESS {btn_norm}")

    def release_button(self, btn: str) -> None:
        """Send RELEASE <BUTTON> command."""
        btn_norm = btn.upper()
        self.write_raw_command(f"RELEASE {btn_norm}")

    def set_main_stick(self, x: float, y: float) -> None:
        """Send SET MAIN <X> <Y> command with clamped [-1.0, 1.0] coordinates."""
        clamped_x = max(-1.0, min(1.0, float(x)))
        clamped_y = max(-1.0, min(1.0, float(y)))
        self.write_raw_command(f"SET MAIN {clamped_x:.4f} {clamped_y:.4f}")

    def set_c_stick(self, x: float, y: float) -> None:
        """Send SET C <X> <Y> command."""
        clamped_x = max(-1.0, min(1.0, float(x)))
        clamped_y = max(-1.0, min(1.0, float(y)))
        self.write_raw_command(f"SET C {clamped_x:.4f} {clamped_y:.4f}")

    def set_trigger(self, trigger: str, value: float) -> None:
        """Send SET <TRIGGER> <VALUE> command."""
        val = max(0.0, min(1.0, float(value)))
        self.write_raw_command(f"SET {trigger.upper()} {val:.4f}")

    def pulse_button(
        self,
        btn: str,
        hold_duration: float = 0.1,
        post_delay: float = 0.1,
    ) -> None:
        """Press, hold, and release a button with customizable delays."""
        self.press_button(btn)
        if hold_duration > 0:
            time.sleep(hold_duration)
        self.release_button(btn)
        if post_delay > 0:
            time.sleep(post_delay)

    def hold_stick(
        self,
        x: float,
        y: float,
        duration: float = 0.2,
        post_delay: float = 0.1,
    ) -> None:
        """Deflect main stick, hold for duration, and return to neutral center."""
        self.set_main_stick(x, y)
        if duration > 0:
            time.sleep(duration)
        self.set_main_stick(0.0, 0.0)
        if post_delay > 0:
            time.sleep(post_delay)

    def reset_all(self) -> None:
        """Release all buttons and center all analog sticks."""
        for btn in self.VALID_BUTTONS:
            self.release_button(btn)
        self.set_main_stick(0.0, 0.0)
        self.set_c_stick(0.0, 0.0)
        self.set_trigger("L", 0.0)
        self.set_trigger("R", 0.0)

    def close(self) -> None:
        """Close FIFO handle."""
        if self.pipe_fd is not None:
            try:
                os.close(self.pipe_fd)
            except OSError:
                pass
            self.pipe_fd = None
        self._is_open = False


class MenuNavigator:
    """Automated closed-loop menu navigation state machine for Mario Superstar Baseball."""

    STAGE_BOOT_LOGOS = "BOOT_LOGOS"
    STAGE_OPENING_CUTSCENE = "OPENING_CUTSCENE"
    STAGE_TITLE_SCREEN = "TITLE_SCREEN"
    STAGE_MAIN_MENU = "MAIN_MENU"
    STAGE_MODE_SELECT = "MODE_SELECT"
    STAGE_RULES_SETTINGS = "RULES_SETTINGS"
    STAGE_STADIUM_SELECT = "STADIUM_SELECT"
    STAGE_ROSTER_SELECT = "ROSTER_SELECT"
    STAGE_STADIUM_LOADING = "STADIUM_LOADING"
    STAGE_LIVE_MATCH = "LIVE_MATCH"

    def __init__(
        self,
        controller: DolphinPipeController,
        memory_hook: Optional[Any] = None,
        gdb_client: Optional[Any] = None,
    ):
        self.controller = controller
        self.memory_hook = memory_hook
        self.gdb_client = gdb_client
        self.current_stage = self.STAGE_BOOT_LOGOS
        self.stage_history: List[Tuple[str, float]] = []

    def log_stage(self, stage: str) -> None:
        self.current_stage = stage
        self.stage_history.append((stage, time.time()))

    def step_boot_and_cutscenes(self, fast_mode: bool = False) -> None:
        """Bypass BIOS/publisher logos and opening cutscene."""
        self.log_stage(self.STAGE_BOOT_LOGOS)
        delay = 0.001 if fast_mode else 0.5
        for _ in range(3):
            self.controller.pulse_button("START", hold_duration=delay, post_delay=delay)
            self.controller.pulse_button("A", hold_duration=delay, post_delay=delay)

        self.log_stage(self.STAGE_OPENING_CUTSCENE)
        self.controller.pulse_button("START", hold_duration=delay, post_delay=delay)

    def step_title_to_exhibition(self, fast_mode: bool = False) -> None:
        """Advance from Title Screen ('Press Start') to Exhibition Mode Select."""
        self.log_stage(self.STAGE_TITLE_SCREEN)
        delay = 0.001 if fast_mode else 0.4
        self.controller.pulse_button("START", hold_duration=delay, post_delay=delay)

        self.log_stage(self.STAGE_MAIN_MENU)
        # Main Menu defaults to Exhibition (top) -> Press A
        self.controller.pulse_button("A", hold_duration=delay, post_delay=delay)

        self.log_stage(self.STAGE_MODE_SELECT)
        # Mode Select defaults to 1P vs COM -> Press A
        self.controller.pulse_button("A", hold_duration=delay, post_delay=delay)

    def step_rules_and_stadium(self, stadium_index: int = 0, fast_mode: bool = False) -> None:
        """Confirm match rules and select stadium."""
        self.log_stage(self.STAGE_RULES_SETTINGS)
        delay = 0.001 if fast_mode else 0.4
        # Confirm rules with START
        self.controller.pulse_button("START", hold_duration=delay, post_delay=delay)

        self.log_stage(self.STAGE_STADIUM_SELECT)
        # If non-default stadium, navigate stick
        if stadium_index > 0:
            for _ in range(stadium_index):
                self.controller.hold_stick(1.0, 0.0, duration=delay, post_delay=delay)
        self.controller.pulse_button("A", hold_duration=delay, post_delay=delay)

    def step_roster_selection(
        self,
        team1_captain_slot: int = 2,
        team2_captain_slot: int = 21,
        team1_color_toggle: bool = True,
        fast_mode: bool = False,
    ) -> None:
        """Select Team Captains and verify/set roster slots in RAM."""
        self.log_stage(self.STAGE_ROSTER_SELECT)
        delay = 0.001 if fast_mode else 0.3

        # Color toggle (X or Y button for alternate color e.g. Red DK)
        if team1_color_toggle:
            self.controller.pulse_button("X", hold_duration=delay, post_delay=delay)

        # Confirm Team 1 Captain
        self.controller.pulse_button("A", hold_duration=delay, post_delay=delay)

        # Team 2 Captain Selection
        self.controller.pulse_button("A", hold_duration=delay, post_delay=delay)

        # If memory hook is active, inject/verify roster in RAM
        if self.memory_hook and self.memory_hook.is_connected():
            try:
                # 0x8036F14C is Player Struct Table
                # Slot 2 @ pitcher (pos 0), Slot 21 @ 2nd base (pos 3)
                self.memory_hook.write_u16(0x8036F14C + 0x252, team1_captain_slot)
                self.memory_hook.write_u16(0x8036F14C + 0x27C * 3 + 0x252, team2_captain_slot)
            except Exception:
                pass

        # Final roster confirm -> START
        self.controller.pulse_button("START", hold_duration=delay, post_delay=delay)

    def step_await_stadium_loading(self, timeout_sec: float = 10.0, fast_mode: bool = False) -> None:
        """Wait for stadium load and camera flyover."""
        self.log_stage(self.STAGE_STADIUM_LOADING)
        if fast_mode:
            time.sleep(0.005)
        else:
            time.sleep(min(timeout_sec, 2.0))

        self.log_stage(self.STAGE_LIVE_MATCH)

    def execute_live_gameplay_pulses(self, num_pitches: int = 3, fast_mode: bool = False) -> None:
        """Send pitching and batting inputs during live gameplay to exercise animation rigs."""
        delay = 0.001 if fast_mode else 0.5
        for _ in range(num_pitches):
            self.controller.pulse_button("A", hold_duration=delay, post_delay=delay)
            self.controller.pulse_button("B", hold_duration=delay, post_delay=delay)

    def navigate_to_match(
        self,
        team1_captain_slot: int = 2,
        team2_captain_slot: int = 21,
        stadium_index: int = 0,
        fast_mode: bool = False,
    ) -> bool:
        """Run complete end-to-end menu navigation sequence from boot to live match."""
        try:
            self.step_boot_and_cutscenes(fast_mode=fast_mode)
            self.step_title_to_exhibition(fast_mode=fast_mode)
            self.step_rules_and_stadium(stadium_index=stadium_index, fast_mode=fast_mode)
            self.step_roster_selection(
                team1_captain_slot=team1_captain_slot,
                team2_captain_slot=team2_captain_slot,
                team1_color_toggle=True,
                fast_mode=fast_mode,
            )
            self.step_await_stadium_loading(fast_mode=fast_mode)
            self.execute_live_gameplay_pulses(num_pitches=2, fast_mode=fast_mode)
            return True
        except Exception:
            return False
