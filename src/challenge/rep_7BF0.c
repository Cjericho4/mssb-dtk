#include "challenge/rep_7BF0.h"

// .text:0x0002858C size:0x434
void fn_1_2858C(void) {
    return;
}

// .text:0x000289C0 size:0x20
void fn_1_289C0(Rep7978Camera* camera) {
    fn_1_273D8(camera);
}

// .text:0x000289E0 size:0x100
s32 fn_1_289E0(ChallengeScript* script, u16 buttons) {
    ChallengeScriptGlobals* globals = &lbl_1_data_11300;
    switch ((s8)globals->selection) {
    case 0:
        if (buttons & 0x100) globals->selection = 2;
        else if (buttons & 0x400) {
            globals->pending = 1;
            globals->selection = 1;
        }
        break;
    case 1:
        if (buttons & 0x100) globals->selection = 2;
        else if (buttons & 0x200) globals->selection = 0;
        else if (buttons & 0x400) globals->pending = 1;
        break;
    case 2:
        if (buttons & 0x100) globals->selection = 1;
        else if (buttons & 0x200) globals->selection = 0;
        break;
    }
    script->entries[script->timer].data = lbl_1_data_11424[(s8)globals->selection];
    return 0;
}

// .text:0x00028AE0 size:0x154
void fn_1_28AE0(void) {
    return;
}

// .text:0x00028C34 size:0xB4
void fn_1_28C34(void) {
    return;
}

// .text:0x00028CE8 size:0x374
void fn_1_28CE8(DrawingSceneStruct* scene) {
    return;
}

// .text:0x0002905C size:0x300
extern Rep7BF0View471D8 lbl_1_bss_47068;
struct ChallengeTransformScript;
extern struct ChallengeTransformScript lbl_1_data_1133C;
void fn_800383BC(Rep7BF0View471D8* view);
void fn_80037054(Rep7BF0View471D8* view, struct ChallengeTransformScript* script);
void fn_1_2905C(void) {
    Mtx rotation;
    switch ((s8)lbl_1_data_11300.selection) {
    case 0:
        fn_80037768(&lbl_1_bss_47068, 2, lbl_1_data_11300.mode,
            lbl_1_data_11300.bounds[0] / 100000.0f, lbl_1_data_11300.bounds[1] / 100000.0f,
            lbl_1_data_11300.bounds[2] / 100000.0f, lbl_1_data_11300.bounds[3] / 100000.0f);
        lbl_1_bss_47068.direction.x = 0;
        lbl_1_bss_47068.direction.y = lbl_1_data_11300.height / 100000.0f;
        lbl_1_bss_47068.direction.z = 0;
        lbl_1_bss_47068.localPosition.x = lbl_1_data_11300.position[0] / 100000.0f;
        lbl_1_bss_47068.localPosition.y = lbl_1_data_11300.position[1] / 100000.0f;
        lbl_1_bss_47068.localPosition.z = lbl_1_data_11300.position[2] / 100000.0f;
        PSMTXMultVec(lbl_1_bss_47068.transform, &lbl_1_bss_47068.localPosition, &lbl_1_bss_47068.worldPosition);
        lbl_1_bss_47068.normal.x = lbl_1_data_11300.normal[0] / 100000.0f;
        lbl_1_bss_47068.normal.y = lbl_1_data_11300.normal[1] / 100000.0f;
        lbl_1_bss_47068.normal.z = lbl_1_data_11300.normal[2] / 100000.0f;
        PSMTXRotRad(rotation, 'X', 0.017453292f * (lbl_1_data_11300.rotation / 100000.0f));
        C_QUATMtx(&lbl_1_bss_47068.rotation, rotation);
        fn_800383BC(&lbl_1_bss_47068);
        break;
    case 1:
        if ((s8)lbl_1_data_11300.pending == 0) break;
        lbl_1_data_11300.pending = 0;
    case 2:
        lbl_1_bss_47068.frame = lbl_1_data_11300.frame / 100000.0f;
        fn_80037054(&lbl_1_bss_47068, &lbl_1_data_1133C);
        break;
    }
}

// .text:0x0002935C size:0xB8
void fn_1_2935C(Rep7BF0View471D8* view) {
    fn_80037768(view, 2, lbl_1_data_11300.mode, (f32)lbl_1_data_11300.bounds[0] / 100000.0f, (f32)lbl_1_data_11300.bounds[1] / 100000.0f, (f32)lbl_1_data_11300.bounds[2] / 100000.0f, (f32)lbl_1_data_11300.bounds[3] / 100000.0f);
}

// .text:0x00029414 size:0x78
void fn_1_29414(DrawingSceneStruct* scene) {
    if (scene->flag14 != 0) {
        fn_80048BEC(&lbl_1_bss_471BC, 0, 0);
    }
    fn_1_272DC(&lbl_1_bss_471D8.camera, 0);
    fn_1_AF4(10, 10, 1.0f);
    fn_1_28CE8(scene);
}

// .text:0x0002948C size:0x15C
void fn_1_2948C(void) {
    return;
}

// .text:0x000295E8 size:0x460
void fn_1_295E8(void) {
    return;
}

// .text:0x00029A48 size:0x54
void fn_1_29A48(void) {
    fn_800AD038(lbl_80366158.unk8);
    fn_800A97D0(0x10, 0x1E);
    lbl_803CC1B8->currentDrawingItem->loadingState = 1;
    fn_800B0A14_removeQueue();
}

// .text:0x00029A9C size:0x1C0
void fn_1_29A9C(void) {
    return;
}
