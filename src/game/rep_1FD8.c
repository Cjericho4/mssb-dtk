#include "game/rep_1FD8.h"
#include "header_rep_data.h"
#include "UnknownHeaders.h"
#include "game/rep_1D58.h"
#include "game/rep_3448.h"
#include "game/rep_AC8.h"
#include "game/particle_spawn.h"

extern f32 lbl_3_rodata_21F0;
extern u32 lbl_3_bss_9D84;

extern void fn_800BF058(void (*fn)(void));
extern void fn_800BDF70(void** ptr);

typedef struct {
    void* _0;
    u8 _4[0x94];
    u8 unk98; /* 0x98 */
} C23E0Inner;

typedef struct {
    u8 _pad0[0x8];
    Mtx mtx;                    /* 0x08 */
    DrawingSceneStruct* scene;  /* 0x38 */
} CameraSlot_17804;             /* size 0x3C */

typedef struct {
    u8 _pad0[0x40];
    Mtx mtx; /* 0x40 */
} CameraMtx_52768;

extern s32 lbl_3_bss_9D90;
extern Control* lbl_3_bss_9D94;

typedef struct C2310Bone {
    u8 _pad0[0x14];
    struct DODisplayObj* dispObj; /* 0x14 */
    u8 _pad18[0xEC - 0x18];
    MtxPtr worldMtx;              /* 0xEC */
    u8 _padF0[0x100 - 0xF0];
    struct C2310Bone* next;       /* 0x100 */
} C2310Bone;

typedef struct C2310Actor {
    u8 _pad0[0x14];
    struct DODisplayObj* skinObject;  /* 0x14 */
    u8 _pad18[0x64 - 0x18];
    MtxPtr skinMtxArray;              /* 0x64 */
    MtxPtr skinInvTransposeMtxArray;  /* 0x68 */
    u8 _pad6C[0x74 - 0x6C];
    C2310Bone* drawList;              /* 0x74 */
    u8 _pad78[0x7C - 0x78];
    u32 unk7C;                        /* 0x7C */
} C2310Actor;

typedef struct C2310Holder {
    C2310Actor* actor; /* 0x00 */
} C2310Holder;

extern void DOVARenderSkin(struct DODisplayObj* dispObj, MtxPtr camera, MtxPtr mtxArray, MtxPtr invTransposeMtxArray,
                           u8 numLights, struct DOVaList* list);
extern void DOSetWorldMatrix(struct DODisplayObj* dispObj, MtxPtr m);
extern void fn_8003A8A0(struct DODisplayObj* dispObj, MtxPtr camera, s32 arg2);
extern u8 lbl_803CBBC0;
extern CameraSlot_17804 lbl_3_data_17804[];
extern CameraMtx_52768* fn_80052768(s32 arg0);
extern void fn_800A7D4C(s32 arg0, CameraSlot_17804* slot);

// .text:0x000C1964 size:0x10 mapped:0x807009F8
void fn_3_C1964(void) {
    lbl_3_bss_9D9C = 1;
}

// .text:0x000C1974 size:0x54 mapped:0x80700A08
void fn_3_C1974(u8 *arg0) {
    QueueEntry *q = fn_800B0A5C_insertQueue(fn_3_C2644, 4);
    q->unk10 = 0;
    lbl_3_bss_9D98 = arg0 + 0x3C4;
    lbl_3_bss_9D9C = 0;
}

// .text:0x000C19C8 size:0x250 mapped:0x80700A5C
void fn_3_C19C8(void) {
    return;
}

// .text:0x000C1C18 size:0x62C mapped:0x80700CAC
void fn_3_C1C18(void) {
    return;
}

// .text:0x000C2244 size:0xCC mapped:0x807012D8
void fn_3_C2244(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    if (lbl_3_bss_9D9C != 0) {
        lbl_3_bss_9D90 = 0;
        fn_800B0A14_removeQueue();
    } else if (scene->field17_0x2a != 0) {
        fn_800A7D4C(1, &lbl_3_data_17804[lbl_803CBBC0]);
        PSMTXCopy(fn_80052768(0)->mtx, lbl_3_data_17804[lbl_803CBBC0].mtx);
        lbl_3_data_17804[lbl_803CBBC0].scene = scene;
    }
}

// .text:0x000C2310 size:0xD0 mapped:0x807013A4
void fn_3_C2310(C2310Holder* holder, MtxPtr camera) {
    Mtx viewMtx;
    Mtx ctrlMtx;
    C2310Actor* actor;
    C2310Bone* bone;

    CTRLBuildMatrix(lbl_3_bss_9D94, ctrlMtx);
    PSMTXConcat(camera, ctrlMtx, viewMtx);
    actor = holder->actor;
    bone = actor->drawList;
    if (actor->skinObject != NULL) {
        if (actor->unk7C != 0) {
            fn_8003A8A0(actor->skinObject, viewMtx, 1);
        } else {
            DOVARenderSkin(actor->skinObject, viewMtx, actor->skinMtxArray, actor->skinInvTransposeMtxArray, 0, NULL);
        }
    }
    while (bone != NULL) {
        if (bone->dispObj != NULL) {
            DOSetWorldMatrix(bone->dispObj, bone->worldMtx);
            fn_8003A8A0(bone->dispObj, viewMtx, 0);
        }
        bone = bone->next;
    }
}

// .text:0x000C23E0 size:0xC0 mapped:0x80701474
void fn_3_C23E0(void) {
    StadiumObjectElem* obj;
    s32 i;

    fn_800BF058(fn_3_B8184);
    for (i = 0; i < (s32)lbl_3_common_bss_350E4[0].memcpyCount; i++) {
        obj = &lbl_3_common_bss_350E4[0].src[i];
        fn_3_B828C((StadiumObject*)obj);
        if (i >= 1 && i < 11 && obj->flag90_80 && obj->unk74 != NULL) {
            ((C23E0Inner*)*obj->unk74)->unk98 = obj->unk93 | 6;
            fn_800BDF70(obj->unk74);
        }
    }
}

// .text:0x000C24A0 size:0x1A4 mapped:0x80701534
void fn_3_C24A0(void) {
    return;
}

// .text:0x000C2644 size:0x330 mapped:0x807016D8
void fn_3_C2644(void) {
    return;
}

// .text:0x000C2974 size:0x18 mapped:0x80701A08
void fn_3_C2974(void) {
    lbl_3_bss_9DE7 = TRUE;
    lbl_3_bss_9D82 = TRUE;
}

// .text:0x000C298C size:0x114 mapped:0x80701A20
void fn_3_C298C(void) {
    return;
}

// .text:0x000C2AA0 size:0x1E0 mapped:0x80701B34
void fn_3_C2AA0(void) {
    return;
}

// .text:0x000C2C80 size:0x25C mapped:0x80701D14
void fn_3_C2C80(void) {
    return;
}

// .text:0x000C2EDC size:0x214 mapped:0x80701F70
void fn_3_C2EDC(void) {
    return;
}

// .text:0x000C30F0 size:0x57C mapped:0x80702184
void fn_3_C30F0(void) {
    return;
}

// .text:0x000C366C size:0x35C mapped:0x80702700
void fn_3_C366C(void *arg0, u8 arg1) {
    return;
}

// .text:0x000C39C8 size:0x70 mapped:0x80702A5C
void fn_3_C39C8(void) {
    u32 i = 0;
    do {
        void *obj = (void *)fn_80033A24(fn_3_C30F0, 0x80, 0, 0x15, 1, 0);
        if (obj != 0) {
            fn_3_C366C(obj, (u8)i);
        }
        i++;
    } while (i < 6);
}

// .text:0x000C3A38 size:0x1F4 mapped:0x80702ACC
void fn_3_C3A38(void) {
    return;
}

// .text:0x000C3C2C size:0x268 mapped:0x80702CC0
void fn_3_C3C2C(void) {
    return;
}

// .text:0x000C3E94 size:0xDC mapped:0x80702F28
typedef struct {
    u8 _pad0[0x14];
    u16 baseIdx; /* 0x14 */
} Bss9E50Obj;

typedef struct {
    Bss9E50Obj* obj; /* 0x00 */
    u8 _pad4[0xB8];
} Bss9E50;

extern Bss9E50 lbl_3_bss_9E50;
extern void fn_800528C0(f32 x, f32 y, f32 z, s16* outX, s16* outY);

// .text:0x000C3E94 size:0xDC mapped:0x80702F28
void fn_3_C3E94(Vec* pos, s32 idx) {
    s16 sx;
    s16 sy;

    fn_800528C0(pos->x, pos->y, pos->z, &sx, &sy);
    lbl_80371C30[lbl_3_bss_9E50.obj->baseIdx + idx].obj->pos.x = sx;
    lbl_80371C30[lbl_3_bss_9E50.obj->baseIdx + idx].obj->pos.y = sy;
    lbl_80371C30[lbl_3_bss_9E50.obj->baseIdx + idx].obj->pos.z = 0.0f;
}

// .text:0x000C3F70 size:0xF8 mapped:0x80703004
typedef struct C3F70Elem {
    u8 type;       /* 0x00 */
    u8 _pad1[0x3];
    u32 flags;     /* 0x04 */
    u8 _pad8[0x8];
} C3F70Elem;       /* size 0x10 */

typedef struct C3F70List {
    u8 _pad0[0x4];
    C3F70Elem* elems; /* 0x04 */
    u16 count;        /* 0x08 */
} C3F70List;

typedef struct C3F70Part {
    u8 _pad0[0x10];
    C3F70List* list; /* 0x10 */
} C3F70Part;

typedef struct C3F70Node {
    u8 _pad0[0x14];
    C3F70Part* part; /* 0x14 */
} C3F70Node;

typedef struct C3F70Model {
    u8 _pad0[0x6];
    u16 nodeCount;      /* 0x06 */
    u8 _pad8[0x10];
    C3F70Node** nodes;  /* 0x18 */
} C3F70Model;

extern u32 lbl_3_bss_9D88;
extern u16 lbl_3_data_177F0;

// .text:0x000C3F70 size:0xF8 mapped:0x80703004
void fn_3_C3F70(ActorObject* arg0) {
    C3F70Model* model = arg0->wrapper->boneData;
    C3F70Part* part;
    u32 i;
    u32 j;
    C3F70Elem* e;

    if (lbl_3_bss_9D88++ > 4) {
        lbl_3_data_177F0++;
        if (lbl_3_data_177F0 > 0x13) {
            lbl_3_data_177F0 = 4;
        }
        lbl_3_bss_9D88 = 0;
    }
    if (lbl_3_bss_9D88 == 0) {
        for (i = 0; i < model->nodeCount; i++) {
            part = model->nodes[i]->part;
            if (part != NULL) {
                e = part->list->elems;
                for (j = 0; j < part->list->count; j++) {
                    if (e->type == 1) {
                        e->flags &= ~0x1FFF;
                        e->flags |= lbl_3_data_177F0;
                    }
                    e++;
                }
            }
        }
    }
}

// .text:0x000C4068 size:0x84 mapped:0x807030FC
void fn_3_C4068(ActorObject* arg0) {
    hugeAnimStruct* has = (hugeAnimStruct*)arg0->wrapper->boneData;
    AnimObject* obj = has->entries_18->field_0x4->ptr14->ptr10->ptr04;
    u16 frame = obj->flags & 0x1FFF;

    if (lbl_3_bss_9D84++ > 4) {
        frame++;
        if (frame > 0x13) {
            frame = 4;
        }
        lbl_3_bss_9D84 = 0;
    }
    obj->flags &= ~0x1FFF;
    obj->flags |= frame;
}

// .text:0x000C40EC size:0x60 mapped:0x80703180
void fn_3_C40EC(ActorObject* arg0) {
    hugeAnimStruct* has = (hugeAnimStruct*)arg0->wrapper->boneData;
    u8 byte_a9 = arg0->field_0xa9;
    AnimLevel1* level1 = has->entries_18->field_0x4;
    AnimLevel2* level2 = level1->ptr14;
    AnimLevel4* level4 = level2->ptr10;
    AnimObject* obj = level4->ptr04;

    if (byte_a9 != 6) {
        obj->flags &= ~0x1FFF;
        obj->flags |= 0x19;
    } else {
        obj->flags &= ~0x1FFF;
        obj->flags |= 0x1a;
    }
}

// .text:0x000C414C size:0x158 mapped:0x807031E0
void fn_3_C414C(void) {
    return;
}

// .text:0x000C42A4 size:0x1A8 mapped:0x80703338
void fn_3_C42A4(void) {
    return;
}

// .text:0x000C444C size:0x2D8 mapped:0x807034E0
void fn_3_C444C(void) {
    return;
}

// .text:0x000C4724 size:0x1AC mapped:0x807037B8
void fn_3_C4724(void) {
    return;
}

// .text:0x000C48D0 size:0x2B0 mapped:0x80703964
void fn_3_C48D0(void) {
    return;
}

// .text:0x000C4B80 size:0x174 mapped:0x80703C14
void fn_3_C4B80(void) {
    return;
}

// .text:0x000C4CF4 size:0x20C mapped:0x80703D88
void fn_3_C4CF4(void) {
    return;
}

// .text:0x000C4F00 size:0x404 mapped:0x80703F94
void fn_3_C4F00(void) {
    return;
}

// .text:0x000C5304 size:0x1CC mapped:0x80704398
void fn_3_C5304(void) {
    return;
}

// .text:0x000C54D0 size:0x218 mapped:0x80704564
void fn_3_C54D0(void) {
    return;
}

// .text:0x000C56E8 size:0x294 mapped:0x8070477C
void fn_3_C56E8(void) {
    return;
}

// .text:0x000C597C size:0x364 mapped:0x80704A10
void fn_3_C597C(void) {
    return;
}

// .text:0x000C5CE0 size:0xFC mapped:0x80704D74
typedef struct C5CE0Arg {
    u8 _pad0[0x9C];
    Vec pos; /* 0x9C */
} C5CE0Arg;

// .text:0x000C5CE0 size:0xFC mapped:0x80704D74
BOOL fn_3_C5CE0(C5CE0Arg* arg0) {
    VecXYZ fpos = {0.0f, 0.0f, 0.0f};
    Vec diff;
    u32 i;

    if (g_GameLogic.gameStatus == 2 && g_GameLogic.playOver != 0) {
        return FALSE;
    }
    for (i = 0; i < 9; i++) {
        memset(&fpos, 0, sizeof(fpos));
        fn_8001B728(i, 4, &fpos);
        PSVECSubtract((Vec*)&fpos, &arg0->pos, &diff);
        if (PSVECMag(&diff) <= 2.6f) {
            fn_3_25844(i, 1);
            return TRUE;
        }
    }
    return FALSE;
}

// .text:0x000C5DDC size:0x480 mapped:0x80704E70
void fn_3_C5DDC(void) {
    return;
}

// .text:0x000C625C size:0x174 mapped:0x807052F0
void fn_3_C625C(void) {
    return;
}

// .text:0x000C63D0 size:0xDFC mapped:0x80705464
void fn_3_C63D0(void) {
    return;
}

// .text:0x000C71CC size:0x278 mapped:0x80706260
void fn_3_C71CC(void) {
    return;
}

// .text:0x000C7444 size:0x58 mapped:0x807064D8
void fn_3_C7444(ActorObject* arg0) {
    hugeAnimStruct* has = (hugeAnimStruct*)arg0->wrapper->boneData;
    int state = arg0->state;
    AnimLevel1* level1 = has->entries_18->unk34;
    AnimLevel2* level2 = level1->ptr14;
    AnimLevel4* level4 = level2->ptr10;
    AnimObject* obj = level4->ptr04;

    if (state == 0) {
        obj->flags &= ~0x1FFF;
        obj->flags |= 2;
        return;
    } else {
        obj->flags &= ~0x1FFF;
        return;
    }
    return;
}

// .text:0x000C749C size:0x11C mapped:0x80706530
void fn_3_C749C(void) {
    return;
}

// .text:0x000C75B8 size:0x1F4 mapped:0x8070664C
void fn_3_C75B8(void) {
    return;
}

// .text:0x000C77AC size:0x260 mapped:0x80706840
void fn_3_C77AC(void) {
    return;
}

// .text:0x000C7A0C size:0x650 mapped:0x80706AA0
void fn_3_C7A0C(void) {
    return;
}

// .text:0x000C805C size:0x1E0 mapped:0x807070F0
void fn_3_C805C(void) {
    return;
}

// .text:0x000C823C size:0x78 mapped:0x807072D0
struct StadiumModel* fn_3_C823C(s32 arg0, Mtx m) {
    StadiumObjectElem* obj;

    obj = &lbl_3_common_bss_350E4[0].src[arg0];
    CTRLBuildMatrix((Control*)obj, m);
    if (obj->unk_A9 == 5) {
        m[1][3] = lbl_3_rodata_21F0;
    }
    return lbl_3_common_bss_350E4[0].src[arg0].unk_78;
}

// .text:0x000C82B4 size:0x39C mapped:0x80707348
void fn_3_C82B4(void) {
    return;
}

// .text:0x000C8650 size:0xD2C mapped:0x807076E4
void fn_3_C8650(void) {
    return;
}
