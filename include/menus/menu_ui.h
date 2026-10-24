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
typedef struct MenuUiSpriteBank {
    u16 width, height;
    u8 frameRate, recordWords;
    u16 flags;
    u32 sequencesOffset;
} MenuUiSpriteBank;
typedef struct MenuUiSequenceTable {
    u32 count;
    u32 size;
    u32 sequenceOffsets[1];
} MenuUiSequenceTable;
typedef struct MenuUiSequence {
    u32 flagsAndListCount; /* high bit is a flag; mask before indexing */
    u32 size;
    u32 listOffsets[1];
} MenuUiSequence;
typedef struct MenuUiFrameList {
    u16 count;
    u16 fullRecordBytes;
    /* Variable-size records follow. Retail character lists are stored in
     * descending frame order. Type 0 is a full template; type 2 replaces words. */
} MenuUiFrameList;
typedef struct MenuUiFrame {
    u16 type;
    u16 frame;
    u16 flags;
    u16 textureIndex;
    u32 words[9]; /* full retail character-name/image records are 0x2C bytes */
} MenuUiFrame;
typedef struct MenuUiWordDelta {
    u16 type;
    u16 frame;
    u16 changedWordCount;
    u16 recordWords;
    /* u16 wordIndices[], padded to words, then u32 replacementWords[];
     * indices address the full template after its first 4-byte word. */
} MenuUiWordDelta;
#endif
