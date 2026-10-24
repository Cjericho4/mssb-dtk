#include "Unknown/gap_8000B9C8.h"

// .text:0x8000B9C8 size:0x74
void fn_8000B9C8(void) {
    return;
}

// .text:0x8000BA3C size:0x758
void fn_8000BA3C(void) {
    return;
}

// .text:0x8000C194 size:0xAB8
void fn_8000C194(void) {
    return;
}

// .text:0x8000CC4C size:0x2A4
void fn_8000CC4C(void) {
    return;
}

// .text:0x8000CEF0 size:0x274
/* Query one image list (list 0 skips the sequence's header list).
 * Tables have already been relocated: on-disc relative offsets are pointers.
 * Records are stored count-1, count-2, ... 0, so skip count-frame-1 records;
 * the stored frame halfword is copied, not searched or used as a texture key.
 *
 * Type 0 occupies fullRecordBytes and selects the list's FIRST template,
 * zero-filling to bank.recordWords*4 (the expanded output capacity).
 * Type 1 is an independent bank.recordWords*4-byte full record.
 * Type 2: {type,frame,changedWordCount,recordWords}, u16 word indices
 * (word-aligned), then replacement u32s at the END of the packed record.
 * Copy the template payload, replace the first word with this record's header,
 * then apply replacements backwards. Index 0 addresses output+4, not output+0.
 * Type 3 similarly starts from the template but applies {byteOffset,byteSize}
 * ranges followed by concatenated replacement bytes; offsets start at output+4.
 * Retail character templates are 0x2C bytes: flags at +4, textureIndex at +6.
 * These UI records are unrelated to skeletal animation tracks.
 *
 * Non-matching after three refinement attempts: table indexing folds +8/+12
 * into displacement loads instead of the target's indexed loads; remaining /
 * next-record temporaries use different volatile registers, delta index/value
 * walkers fold offsets differently, and type-3 saved registers are permuted.
 * Semantics and all four record cases follow the target; no matching functions
 * are replaced. Invalid list/frame returns 0 without touching out; valid returns
 * 1, including unknown record types (which leave out untouched), as in retail.
 */
u32 fn_8000CEF0(MenuUiSpriteBank* data, s32 sequence, s32 list, s32 frame, Gap80035DD4Query* out) {
    MenuUiSequence* seq = data->sequences->sequences[sequence];
    MenuUiFrameList* frames;
    MenuUiRecord* record;
    MenuUiFrame* result = (MenuUiFrame*)out;
    s32 remaining;
    u32 expandedBytes;
    if ((u32)list >= (seq->flagsAndListCount & 0x7FFFFFFF) - 1) return 0;
    frames = seq->lists[list + 1];
    remaining = frames->count - frame;
    if (remaining <= 0) return 0;
    record = frames->records;
    while (--remaining) {
        MenuUiRecord* next = record;
        u32 fullWords = (u32)frames->fullRecordBytes >> 2;
        u32 recordWords = data->recordWords;
        switch (record->frame.type & 0x7FFF) {
        case 0: next = (MenuUiRecord*)&record->words[fullWords]; break;
        case 1: next = (MenuUiRecord*)&record->words[recordWords]; break;
        case 2: next = (MenuUiRecord*)&record->words[record->delta.recordWords]; break;
        case 3: next = (MenuUiRecord*)&record->words[record->ranges.recordWords]; break;
        }
        record = next;
    }
    expandedBytes = data->recordWords * 4;
    switch (record->frame.type & 0x7FFF) {
    case 0:
        memset((u8*)result, 0, expandedBytes);
        memcpy((u8*)result, (u8*)frames->records, frames->fullRecordBytes);
        break;
    case 1:
        memcpy((u8*)result, (u8*)record, expandedBytes);
        break;
    case 2: {
        u32* payload;
        s32 count;
        u32* values;
        u16* indices;
        memset((u8*)result, 0, expandedBytes);
        payload = result->words;
        memcpy((u8*)payload, (u8*)frames->records->frame.words, frames->fullRecordBytes - 4);
        memcpy((u8*)result, (u8*)record, 4);
        count = record->delta.changedWordCount;
        values = &record->words[record->delta.recordWords];
        indices = &record->delta.wordIndices[count];
        for (;;) {
            s32 more = count-- != 0;
            --values;
            --indices;
            if (!more) break;
            payload[*indices] = *values;
        }
        break;
    }
    case 3: {
        u8* payload;
        s32 count;
        MenuUiByteRange* range;
        u8* values;
        memset((u8*)result, 0, expandedBytes);
        payload = result->bytes;
        memcpy(payload, frames->records->frame.bytes, frames->fullRecordBytes - 4);
        memcpy((u8*)result, (u8*)record, 4);
        count = record->ranges.rangeCount;
        range = record->ranges.ranges;
        values = (u8*)&range[count];
        while (count-- != 0) {
            memcpy(&payload[range->offset], values, range->size);
            values += range->size;
            ++range;
        }
        break;
    }
    }
    return 1;
}

// .text:0x8000D164 size:0x6D4
void fn_8000D164(void) {
    return;
}

// .text:0x8000D838 size:0x6C
void fn_8000D838(void) {
    return;
}

// .text:0x8000D8A4 size:0x3F8
void fn_8000D8A4(void) {
    return;
}

// .text:0x8000DC9C size:0x394
void fn_8000DC9C(void) {
    return;
}

// .text:0x8000E030 size:0x2A4
void fn_8000E030(void) {
    return;
}

// .text:0x8000E2D4 size:0x490
void fn_8000E2D4(void) {
    return;
}

// .text:0x8000E764 size:0x58
void fn_8000E764(f32 angle, Gap8000B9C8Direction* direction) {
    direction->sine = (f32)sin(angle);
    direction->cosine = (f32)cos(angle);
}

// .text:0x8000E7BC size:0x144
void fn_8000E7BC(void) {
    return;
}

// .text:0x8000E900 size:0x30C
void SetSpriteRect(void) {
    return;
}

// .text:0x8000EC0C size:0x310
void fn_8000EC0C(void) {
    return;
}

// .text:0x8000EF1C size:0x234
void AddVec2iToQuad(void) {
    return;
}

// .text:0x8000F150 size:0x298
void fn_8000F150(void) {
    return;
}

// .text:0x8000F3E8 size:0xA4
void fn_8000F3E8(s32 type) {
    Gap8000B9C8PoolNode* node = &lbl_800E9908[lbl_803CBBC0];
    switch (type) {
    case -1:
        node->value = lbl_803CB760[4];
        break;
    case 4:
        node->value = lbl_803CB760[1];
        break;
    case 5:
        node->value = lbl_803CB760[0];
        break;
    case 6:
        node->value = lbl_803CB760[2];
        break;
    case 11:
        node->value = lbl_803CB760[3];
        break;
    }
    fn_800A7D4C(0, node);
}

// .text:0x8000F48C size:0x2C
void somethingSetTexturePointer(void) {
    lbl_803CBBE8 = &lbl_800E9920;
    convertTextureHeader(&lbl_800E9920);
}

// .text:0x8000F4B8 size:0x7C
void fn_8000F4B8(s32 a, s32 b, s32 c, s32 d) {
    lbl_80366B18.mask = 0;
    if (a >= 0) {
        lbl_80366B18.mask = 1 << a;
    }
    if (b >= 0) {
        lbl_80366B18.mask |= 1 << b;
    }
    if (c >= 0) {
        lbl_80366B18.mask |= 1 << c;
    }
    if (d >= 0) {
        lbl_80366B18.mask |= 1 << d;
    }
}

// .text:0x8000F534 size:0x3C0
void fn_8000F534(void) {
    return;
}
