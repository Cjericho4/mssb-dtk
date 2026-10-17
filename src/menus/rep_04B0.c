#include "menus/rep_04B0.h"
#include "menus/rep_0438.h"
#include "menus/gap_1254.h"
#include "static/UnknownHomes_Static.h"
#include "menus/rep_08E8.h"

extern void LITXForm(MenusLight* light, Mtx matrix);

extern MenusSceneAsset lbl_2_data_1DD4;
extern void fn_8001CB10(MenusSceneAsset* asset, s32 mode);
extern void fn_8001CCC8(void);
#include "menus/gap_16870.h"

// .text:0x00014574 size:0x21C
void fn_2_14574(void) {
    return;
}

// .text:0x00014790 size:0x428
void fn_2_14790(void) {
    return;
}

// .text:0x00014BB8 size:0xE8
void fn_2_14BB8(void) {
    return;
}

// .text:0x00014CA0 size:0x318
void fn_2_14CA0(void) {
    return;
}

// .text:0x00014FB8 size:0x118
void fn_2_14FB8(void) {
    return;
}

// .text:0x000150D0 size:0x34
void fn_2_150D0(u8 index) {
    if (lbl_2_bss_100B8.active[index] == 0) {
        lbl_2_bss_100B8.active[index] = 1;
        lbl_2_bss_100B8.counters[index] = 0;
    }
}

// .text:0x00015104 size:0xB8
void fn_2_15104(void) {
    return;
}

// .text:0x000151BC size:0x450
void fn_2_151BC(void) {
    return;
}

// .text:0x0001560C size:0x484
void fn_2_1560C(void) {
    return;
}

// .text:0x00015A90 size:0x6C
void fn_2_15A90(void) {
    return;
}

// .text:0x00015AFC size:0x384
void fn_2_15AFC(void) {
    return;
}

// .text:0x00015E80 size:0x59C
void fn_2_15E80(void) {
    return;
}

// .text:0x0001641C size:0x44
void fn_2_1641C(void) {
    fn_2_1A88();
    lbl_8034E9A0.unk46FC = 0;
    lbl_8034E9A0.unk46FD = -1;
    lbl_8034E9A0.unk46FE = -1;
    lbl_8034E9A0.unk46FF = -1;
    lbl_8034E9A0.unk4729 = 0;
}

// .text:0x00016460 size:0x204
void fn_2_16460(void) {
    return;
}

// .text:0x00016664 size:0x68
void fn_2_16664(void) {
    hugeAnimStruct* anim = &g_hugeAnimStruct;
    MenusLightMatrixState* state = &lbl_2_bss_10164;
    f32 (*matrix)[4] = state->matrix;
    s32 i = 0;
    do {
        LITXForm(anim->menuLights[i], matrix);
        i++;
    } while (i < 4);
}

// .text:0x000166CC size:0x58
void fn_2_166CC(void) {
    GameInitVariables* settings = &g_d_GameSettings;
    u8 stadium = settings->StadiumID;
    settings->StadiumID = 0;
    fn_8001CB10(&lbl_2_data_1DD4, 4);
    fn_8001CCC8();
    settings->StadiumID = stadium;
}

// .text:0x00016724 size:0x14C
void fn_2_16724(void) {
    return;
}
