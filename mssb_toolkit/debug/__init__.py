"""Debugging and memory inspection tools for Mario Superstar Baseball."""

from mssb_toolkit.debug.gdb_client import (
    CrashContext,
    DolphinGDBClient,
    GDBRemoteProtocol,
    MockGDBServer,
    PowerPCRegisters,
    PPCStackUnwinder,
    StackFrame,
)
from mssb_toolkit.debug.memory_hook import (
    DolphinMemoryEngineBackend,
    GDBMemoryBackend,
    GameCubeMemoryHook,
    InvalidGameCubeAddressError,
    MemoryBackend,
    MemoryHookConnectionError,
    MockMemoryBackend,
    ProcMemBackend,
    SharedMemBackend,
)
from mssb_toolkit.debug.memory_inspectors import (
    CharacterStagingState,
    GameCubeInspectors,
    GloveAttachmentEntry,
    MasterDescriptorEntry,
    PlayerEntity,
    SubfileEntry,
)
from mssb_toolkit.debug.relocation_auditor import (
    HeapSeparationAuditor,
    ModelRelocationAuditor,
    PointerAuditResult,
    PointerRelocationAuditor,
)

__all__ = [
    "CrashContext",
    "DolphinGDBClient",
    "GDBRemoteProtocol",
    "MockGDBServer",
    "PowerPCRegisters",
    "PPCStackUnwinder",
    "StackFrame",
    "GameCubeMemoryHook",
    "InvalidGameCubeAddressError",
    "MemoryBackend",
    "MemoryHookConnectionError",
    "MockMemoryBackend",
    "ProcMemBackend",
    "SharedMemBackend",
    "GDBMemoryBackend",
    "DolphinMemoryEngineBackend",
    "GameCubeInspectors",
    "SubfileEntry",
    "MasterDescriptorEntry",
    "GloveAttachmentEntry",
    "CharacterStagingState",
    "PlayerEntity",
    "ModelRelocationAuditor",
    "PointerAuditResult",
    "PointerRelocationAuditor",
    "HeapSeparationAuditor",
]

