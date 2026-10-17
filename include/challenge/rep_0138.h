#ifndef __CHALLENGE_rep_0138_H_
#define __CHALLENGE_rep_0138_H_

#include "mssbTypes.h"
void fn_80048C28(void);
void fn_80048C1C(void);
#include "Dolphin/GX/GXGeometry.h"

typedef struct Rep0138Model {
    /* 0x00 */ u8 _pad0[0x68];
    /* 0x68 */ struct Rep0138ModelData* data;
} Rep0138Model;
extern GXCullMode lbl_1_data_8C4;
extern s32 lbl_1_data_848[4];

void fn_1_4E98(void);
void fn_1_54E0(void);
void fn_1_5540(void);
void fn_1_5544(void);
void fn_1_5698(void);
void fn_1_5924(void);
void fn_1_5AC0(void);
void fn_1_6050(void);
void fn_1_6578(void);
void fn_1_66C4(void);
void fn_1_6848(void);
void fn_1_6E14(void);
void fn_1_717C(void);
void fn_1_7280(void);
void fn_1_73B8(Rep0138Model* model, s32 count, ...);
void fn_1_77EC(Rep0138Model* model);
void fn_1_7848(void);
void fn_1_786C(void);
void fn_1_78E4(void);
void fn_1_7960(void);
void fn_1_7E04(void);
void fn_1_7EF8(void);
void fn_1_7FF8(void);
void fn_1_8368(void);

#endif // !__CHALLENGE_rep_0138_H_
