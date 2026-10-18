Skipped __MTGQR5, __MTGQR6, __MTGQR7: inline GQR assembly; fn_8001B214: needs g_hugeAnimStruct.
Extended Gap800B993CColor with a u32 word union view for whole-color copies.
fn_80048C1C: target contains dead load/compare with no result; ordinary C removes them; restored stub.
Skipped fn_8001B200: needs g_hugeAnimStruct.
Extended Gap800B117CObj with unk14, entries at 0x18 and unk134 at 0x134; matching offsets reuse object view.
Skipped SKNBzero32B, SKNFlushByIndex1, SKNFlushByIndex2: cache instruction loops; fn_800111B4: stored offset relocation; fn_800111D8: needs g_hugeAnimStruct.
DSInitTree: subtraction is scheduled before zero store; scalar, pointer and volatile forms disagree; restored stub.
DSInitList: subtraction is scheduled before zero store; scalar, pointer and volatile forms disagree; restored stub.
fn_800E4AC8: call to same-unit empty stub is inlined away; target also has older ABI prologue; restored stub.
Extended Gap800B993CObj with worldMatrix at 0x18, a 3x4 float matrix.
Introduced Gap8001E460Object (fog word at 0x70), opaque Gap8001E460Resource and Gap8001E460ResourceState (resource pointer at 0).
Introduced Gap80032038SortEntry with float sort key at 0x4.
Introduced Gap80062578Status with busy and pending bytes at 0x5D/0x5E.
Introduced opaque Gap8000B9C8Texture for texture-header conversion.
Introduced Gap800A6870Thread (0x318-byte view) embedded at Gap800A6870Load+0x318.
Skipped fn_800189B8: needs g_hugeAnimStruct; fn_800ACF14/fn_800ACFB0: allocation-prefix access at negative offset requires container recovery.
Introduced Gap80039AA8Position (8-byte XY) and Gap80039AA8State positions at 0xCD0.
Introduced Gap80048BECTiming with requested and limit counts at 4 and 8.
Introduced Gap800B508CTrack (flags at 0xF) and Gap800B508CAnimation (time, track/data pointers, frame and flags).
Introduced Gap80042D38State with state/timer history halfwords at 2,4,6,8.
Introduced Gap800506E8Camera, a 0xA8-byte camera entry.
Introduced Gap80062578Request (value at 8) and Gap80062578Sound (sound ID at 0x98).
Introduced Gap80067AC8Sound with sound ID at 0xC0.
Introduced Gap80069B08Queue with priority at 0x12 and active flag at 0x3B.
Extended Gap800BD3A0State with TLUT pointer at 0xC and signed byte at 0x4D; opaque Gap800BD3A0Tlut.
Introduced Gap800AD780DrawEntry (0xC) and Gap800AD780DrawLists with 24-entry banks at 0/0x120.
fn_800A1B80: target uses older compiler ABI (8-byte frame, LR indirect call); configured compiler uses 16-byte frame/CTR; restored stub.
Extended Gap8001E460ResourceState with selector byte at 0x10; skipped fn_80021980: stored offset relocation.
Introduced Gap80032038Node (next at 4, flags at 0x17) and 8-byte sentinel Gap80032038Head.
Extended Gap80062578Sound with sound words at 0x14 and 0x9C.
Introduced Gap80067AC8Status with state byte at 0x2A.
Introduced Gap80048BECMenu with ID halfword at 0x16.
fn_800339F0: byte argument conversion sinks into split loop entry, with differing registers; three variants failed; restored stub.
Introduced Gap800B117CList (size/head/tail), embedded at Obj+0x70; extended Obj matrices at 0x60.
Extended Gap800BD3A0Entry with position Vec at 0x34.
Introduced Gap800B117CVec, a local three-float position vector.
Introduced Gap800BD3A0Vec, a local three-float position vector.
Introduced Gap800DFDD4Header, big-endian width/height decoded into fields at 4/6 and bytes at 8/9.
Extended Gap80035DD4Entry with limit at 0x5C and flag at 0x68, preserving stride 0xC0.
fn_800BEBCC: 12-byte vector copy load grouping and register allocation differ across struct, words and inline by-value forms; restored stub.
fn_80035EEC: remaining r5/r6 allocation swap for shifted limit versus entry offset; restored stub.
Introduced Gap800A6870PoolNode (tagged next word) and Gap800A6870Pools (heads at 0x4C).
Introduced Gap80032038Chain with next pointer at 0 for free-list splicing.
Introduced Gap800B117CMasks with four halfword masks at 6/8/A/C.
Introduced Gap800AD780DrawScript, 0x80-byte entries with leading callback.
Introduced opaque Gap800B117CVertex and Gap800B117CTexture with width/height at 8/A.
Introduced Gap80069B08Tracker using existing Mission entries and row/column bytes at 0x4415/0x4422 (size 0x4508).
Extended Gap8001E460Sound with resource-pointer table at 4, preserving sound settings at 0x396.
Skipped GQRSetup5/6/7: GQR assembly; fn_8001B2D0/fn_8001D110/fn_8001D148/fn_800115C8/fn_80011604/fn_80018B38: needs g_hugeAnimStruct; fn_800ACF78: allocation prefix at negative offsets.
Introduced Gap800B117CAnimation with time/speed/flags17/flags18; extended Obj count at 6 and animation pointer at 0xE8.
Introduced Gap80062578GameState with mode at 0x28, opaque Gap80062578Object, and Gap80062578Setup (leading value).
Introduced opaque Gap80067AC8Object for queue-owned UI objects.
Extended Gap80048BECObj with actorIndex at 0x1FA; opaque Gap80048BECActor.
fn_8006C100: configured optimizer unrolls threshold loop; byte iterator form also differs; restored stub.
Introduced Gap80042D38Task (baseIndex 0x14), Entry (time at 0x5C/active at 0x68), and 8-byte Slot.
Introduced Gap800506E8Cameras holding two primary and two alternate 0xA8-byte cameras (size 0x2A0).
Introduced Gap8004CA48Selection with indices at 0x18 and busy flags at 0x4C.
Defined Gap8001E460Resource with end pointer at 0x18 for allocation size calculation.
Introduced opaque Gap80041348Allocation for allocation result.
Introduced Gap800AD780Hooks with typed byte-buffer allocation/free callbacks.
Extended Gap800B117CFlags with renderMode at 0x78.
Extended Gap8002244CFlags with unk1E9 and flags at 0x1EA.
Introduced opaque Gap800AD780MessageQueue for the movie worker queue.
Introduced Gap80069B08Callback and Gap80069B08Game (mode at 0x28); refined matching callback setter signatures.
Extended Gap800BD3A0State with boundCount (0x24), axis bounds (0x28..0x3C) and vector (0x40..0x48).
Introduced Gap800B117CRequest with type halfword at 4.
Introduced Gap800A6870Semaphore and opaque DVDFile; extended Load with semaphore at 0x630, running at 0x6F0, state at 0x714 and entryNumber at 0x718.
Introduced opaque Gap80035DD4Request/Actor and Gap80035DD4RenderState (index at 0x78).
Extended Gap80039AA8State with counters at 0xA00/A02, 13 flags at 0xCC0 and mode at 0xD38.
Extended Gap8001E460Sound with groupCount at 0x390.
Introduced opaque Gap80069B08RenderMode for VI configuration.
Introduced Gap800AD780Movie with startTime at 0x1A0 and flags at 0x1BA.
Introduced Gap800AD780Ring with cursor, size and byte counters at 0xC..0x20.
Introduced Gap800AD780QueueNode with active/previous/next fields at 0/4/8.
Introduced Gap80064754Settings (side at E) and Gap80064754Mode (mode at 0, option at 3).
fn_800B0A14_removeQueue: three variants leave the first next/previous loads and store registers swapped; retained compiling best attempt.
Extended Gap8000F8F4Entry with data/state/flags; introduced Gap8000F8F4Table and global State with table pointers at 0x798.
Introduced Gap8002244CVector; extended Obj with vector-pointer union at 0 and volatile current index at 0x14.
Extended Gap800A6870Load with memory at 0x6FC and halfword/byte state union at 0x714.
Introduced Gap800B117CFlagBanks (two 24-entry 0x90 banks), TextureSlot (0x1C), CommandBuffer (0x10).
Skipped fn_8001D0D0/fn_8001AAA4: needs g_hugeAnimStruct; convertTextureHeader: stored offset relocation; _OSAllocFromHeap/fn_800ACF34/SndAlloc: allocation-header pointer recovery requires excluded offset arithmetic.
Introduced Gap800B117CTrack (0x10 stride, ID at A) and Sequence (tracks at 4, count at 8).
LinearInterpolateToNewRange: first clamp expression differs in float allocation; restored stub.
Strcmp: signed-byte comparison/increment instruction allocation differs; restored stub.
LinearInterpolateToNewRange: inline normalizer also differs; restored stub after two attempts.
Strcmp: iterative form differs only in symbol-vs-local branch relocation; recursion is automatically inlined; restored original stub after two attempts.
Introduced Gap800B117CDuration and extended Animation with duration pointer at 0xC.
Introduced Gap80064754Stats with options at 0x46F8/46F9; extended Settings mode at 0x10 and options at 0x50/51.
Introduced Gap800A97D0Pad (0x20 stride) with pending/command/value at 9/A/B; extended Pan disabledPads at 6.
Introduced Gap800A6870SleepQueue; extended Pools with framebuffer at 0 and sleep queue at 0x5C.
randRange_FUN_80042bf0: signed range RNG register scheduling differs; restored stub.
Extended Gap8004CA48Selection with transition byte at 0x7E.
Introduced Gap8002244CLoad (complete at 0x715); extended Flags header/records arrays and current/pending words at 0x1CC/1D0.
Extended Gap800A6870Load pending at 0x6F4; Pools period/counter/paused at 0x394/395/396.
randRange_FUN_80042bf0: inline RNG variant also leaves range/random registers swapped; restored stub after two attempts.
Introduced Gap8000B9C8Direction with sine/cosine floats at 0/4.
Introduced Gap800506E8Actor (ID at 0x252) and Task (index/actor/ID at 0x14/18/1C).
Introduced Gap80062578Settings (mode at 0x10); extended Status flags at 0x55 and Words array view.
Introduced Gap800A6870Stream with previous/next/flags/callback at 0/4/8/C; refined stream-head pointer and out-of-line restart stub signature.
Introduced Gap80069B08Scores, 0x16-byte score configuration with order at C and mode at 0x12.
fn_8006C398: score-order loop allocation differs; restored stub.
