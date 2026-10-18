#ifndef __UNKNOWN_gap_80027918_H_
#define __UNKNOWN_gap_80027918_H_

#include "mssbTypes.h"
typedef struct Gap80027918Vec {
    f32 x;
    f32 y;
    f32 z;
} Gap80027918Vec;
typedef struct Gap80027918Node {
    /* 0x00 */ struct Gap80027918Node* prev;
    /* 0x04 */ struct Gap80027918Node* next;
    u8 _pad8[0xF];
    /* 0x17 */ u8 flag : 1;
    /* 0x17 */ u8 type : 7;
    /* 0x18 */ Gap80027918Vec pos;
    /* 0x24 */ Gap80027918Vec prevPos;
    /* 0x30 */ Gap80027918Vec delta;
    u8 _pad3C[0x4];
    /* 0x40 */ u16 unk40;
} Gap80027918Node;
typedef struct Gap80027918List {
    Gap80027918Node* prev;
    Gap80027918Node* next;
} Gap80027918List;
extern Gap80027918List lbl_803CBC84;
void memcpy(Gap80027918Vec* dst, Gap80027918Vec* src, u32 size);
void PSVECSubtract(Gap80027918Vec* a, Gap80027918Vec* b, Gap80027918Vec* out);

void fn_80027918(void);
void fn_80027968(void);
void fn_8002852C(void);
void fn_80028628(void);
void fn_80028F48(void);
void fn_8002955C(void);
void fn_800297F0(void);
void fn_80029CC8(void);
void fn_8002A1CC(void);
void fn_8002A85C(void);
void fn_8002AC68(void);
void fn_8002B014(void);
void fn_8002B400(void);
void fn_8002B7F8(void);
void fn_8002BC84(void);
void fn_8002C2D0(void);
void fn_8002C56C(void);
void fn_8002CDD0(Gap80027918Vec* v);
void fn_8002CE4C(void);
void fn_8002D82C(void);
void fn_8002DC68(Gap80027918Vec* v);
void fn_8002DCE4(void);
void fn_8002E3DC(void);
void fn_8002E828(void);
void fn_8002ECA0(void);
void fn_8002F1AC(void);
void fn_8002F258(void);
void fn_8002F5F4(void);
void fn_8002F9FC(void);
void fn_8002FDB8(void);
void fn_80030470(void);
void fn_80030720(void);
void fn_80030D88(void);
void fn_80031034(void);
void fn_800317C4(void);
void fn_80031CA4(void);
void fn_80031F34(void);

#endif // !__UNKNOWN_gap_80027918_H_
