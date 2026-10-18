#ifndef __UNKNOWN_gap_800506E8_H_
#define __UNKNOWN_gap_800506E8_H_

#include "mssbTypes.h"
typedef struct Gap800506E8Actor { u8 _pad0[0x252]; u8 id; } Gap800506E8Actor;
typedef struct Gap800506E8Task {
    u8 _pad0[0x14];
    s32 index;
    Gap800506E8Actor* actor;
    u8 id;
} Gap800506E8Task;
Gap800506E8Task* fn_800B0A5C_insertQueue(void (*callback)(void), u16 priority);
typedef struct Gap800506E8Camera { u8 _pad0[0xA8]; } Gap800506E8Camera;
typedef struct Gap800506E8Cameras {
    Gap800506E8Camera slots[2];
    Gap800506E8Camera alternate[2];
} Gap800506E8Cameras;
extern Gap800506E8Cameras lbl_803C639C;
extern s32 lbl_803CB880;
typedef struct Gap800506E8State {
    u8 _pad0[0x28];
    /* 0x28 */ s8 slots[0x24];
    u8 _pad4C[0x30];
    /* 0x7C */ u8 unk7C;
    /* 0x7D */ u8 unk7D;
    /* 0x7E */ u8 unk7E;
    u8 _pad7F[0xF];
    /* 0x8E */ u8 unk8E;
    /* 0x8F */ u8 unk8F;
    /* 0x90 */ u8 unk90;
} Gap800506E8State;
extern Gap800506E8State lbl_803C6028;

extern s32 lbl_803CB880;
extern s32 lbl_803CBD14;

typedef struct Gap800506E8Character {
    u8 unk0;
    /* 0x1 */ u8 id;
    u8 _pad2[0x4];
} Gap800506E8Character;
extern Gap800506E8Character lbl_800E8558[54];
extern u8 lbl_800FDE84[0x744];
void fn_800506E8(s8 value, s32 index, BOOL set);
void fn_80050760(void);
BOOL fn_80050F78(s32 mode);
void fn_80050FE8(void);
void fn_8005138C(void);
void fn_80051D00(void);
void fn_80052188(void);
void fn_800521B0(void);
void fn_8005240C(void);
void fn_80052634(Gap800506E8Actor* actor, s32 index);
s32 fn_8005268C(void);
void fn_80052694(void);
Gap800506E8Camera* fn_80052734(s32 index);
Gap800506E8Camera* fn_80052768(s32 index);
void fn_80052798(s32 value);
s32 fn_800527BC(void);
void fn_800527C4(void);

#endif // !__UNKNOWN_gap_800506E8_H_
