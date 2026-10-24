#ifndef MENUS_MENU_UI_H
#define MENUS_MENU_UI_H
#include "mssbTypes.h"

/* One 0x20-byte scene script entry consumed by fn_80034E20/fn_80034F50.
 * type == 3 terminates the array. resource is a logical ID, resolved through
 * lbl_8023D6C0; flags at +0x10 are NOT a resource ID. */
typedef struct MenusSceneScript {
    u16 type;
    u16 sequence;
    f32 x, y;
    u32 textureOverride;
    u16 flags;
    s16 parent;
    u8 resource;
    u8 drawMode;
    u8 _pad16[2];
    f32 scale;
    u8 playMode;
    u8 _pad1D[3];
} MenusSceneScript;

/* On-disc offsets are relative to the start of the enclosing structure.
 * UI roots use the first two words; the remaining three are zero in the
 * common menu resource. This is not the skeletal ANIMBank format. */
typedef struct MenuUiFileHeader {
    u32 texturesOffset;
    u32 spriteBankOffset;
    u32 unused[3];
} MenuUiFileHeader;
typedef struct MenuUiSequenceTable MenuUiSequenceTable;
typedef struct MenuUiSequence MenuUiSequence;
typedef struct MenuUiFrameList MenuUiFrameList;
typedef union MenuUiRecord MenuUiRecord;

typedef struct MenuUiSpriteBank {
    u16 width, height;
    u8 frameRate, recordWords;
    u16 flags;
    /* Disk offset becomes a pointer during bank relocation. */
    union { u32 sequencesOffset; MenuUiSequenceTable* sequences; };
} MenuUiSpriteBank;
typedef struct MenuUiSequenceTable {
    u32 count;
    u32 size;
    /* Same storage before/after relocation. */
    union { u32 sequenceOffsets[1]; MenuUiSequence* sequences[1]; };
} MenuUiSequenceTable;
typedef struct MenuUiSequence {
    u32 flagsAndListCount; /* high bit is a flag; mask before indexing */
    u32 size;
    /* lists[0] is the header list; image layer N is lists[N+1]. */
    union { u32 listOffsets[1]; MenuUiFrameList* lists[1]; };
} MenuUiSequence;
typedef struct MenuUiFrame {
    u16 type;
    u16 frame;
    union {
        struct { u16 flags, textureIndex; u32 remaining[9]; };
        u32 words[10];
        u8 bytes[40];
    }; /* +4: payload; full character records are 0x2C bytes */
} MenuUiFrame;
typedef struct MenuUiWordDelta {
    u16 type;
    u16 frame;
    u16 changedWordCount;
    u16 recordWords;
    u16 wordIndices[1];
    /* u16 wordIndices[], padded to words, then u32 replacementWords[];
     * indices address the full template after its first 4-byte word. */
} MenuUiWordDelta;
/* Type 3 uses byte offsets/lengths relative to the expanded payload (+4),
 * followed by concatenated replacement bytes. Both delta types carry total
 * packed length in recordWords. Runtime relocation fixes table pointers only. */
typedef struct MenuUiByteRange { u16 offset, size; } MenuUiByteRange;
typedef struct MenuUiRangeDelta {
    u16 type, frame, rangeCount, recordWords;
    MenuUiByteRange ranges[1];
} MenuUiRangeDelta;
union MenuUiRecord {
    MenuUiFrame frame;
    MenuUiWordDelta delta;
    MenuUiRangeDelta ranges;
    u32 words[1];
    u8 bytes[1];
};
struct MenuUiFrameList {
    u16 count;
    u16 fullRecordBytes;
    MenuUiRecord records[1];
};
#endif
