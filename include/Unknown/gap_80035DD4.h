#ifndef __UNKNOWN_gap_80035DD4_H_
#define __UNKNOWN_gap_80035DD4_H_

#include "mssbTypes.h"
typedef struct Gap80035DD4Request Gap80035DD4Request;
typedef struct Gap80035DD4Actor Gap80035DD4Actor;
typedef struct Gap80035DD4RenderState { u8 _pad0[0x78]; s32 index; } Gap80035DD4RenderState;
extern Gap80035DD4RenderState lbl_800F79B8;
typedef struct Gap80035DD4Entry {
    u8 _pad0[0x54];
    /* 0x54 */ s32 unk54;
    u8 _pad58[0x4];
    /* 0x5C */ u32 unk5C;
    u8 _pad60[0x8];
    /* 0x68 */ u8 unk68;
    u8 _pad69[0x57];
} Gap80035DD4Entry;
extern Gap80035DD4Entry lbl_8039C3E0[];
void fn_800B0A14_removeQueue(void);

void fn_80035DD4(void);
void fn_80035ED0(s32 index);
void fn_80035EEC(s32 value, s32 index);
void fn_80035F20(void);
void fn_80036134(void);
void fn_80036214(void);
void fn_80036270(void);
void fn_800362F0(void);
void fn_800363D8(void);
void fn_8003649C(void);
void fn_8003656C(void);
void fn_8003664C(void);
void fn_80036824(void);
void fn_800369DC(void);
void fn_80036A3C(void);
void fn_80036C88(void);
void fn_80037054(void);
void fn_8003731C(void);
void fn_80037768(void);
void fn_80037964(void);
void fn_80037984(void);
void fn_80037AA0(void);
void fn_80037B18(void);
void fn_80037BAC(void);
void fn_8003819C(void);
void fn_800383BC(void);
void fn_80038418(void);
void fn_800385F0(void);
void fn_800387B0(void);
void fn_80038B48(void);
void fn_80038CD0(void);
void fn_80038E2C(void);
void fn_80038EC4(Gap80035DD4Request* request, Gap80035DD4Actor** actor, u8 count);
void fn_80038F08(Gap80035DD4Request* request, Gap80035DD4Actor* actor, u32 count);
void fn_80039310(void);
void fn_80039A4C(void);

#endif // !__UNKNOWN_gap_80035DD4_H_
