#include "Unknown/gap_800BD3A0.h"
#include "game/rep_1D58.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXFrameBuffer.h"
#include "Dolphin/GX/GXMisc.h"
#include "Dolphin/OS/OSError.h"

// .text:0x800BD3A0 size:0xC
void LITInitColor(Gap800BD3A0Light* light, Gap800BD3A0Color* color) {
    light->color = *color;
}

// .text:0x800BD3AC size:0x10
void LITInitDir(Gap800BD3A0Light* light, f32 x, f32 y, f32 z) {
    light->dirX = x;
    light->dirY = y;
    light->dirZ = z;
}

// .text:0x800BD3BC size:0x10
void LITInitPos(Gap800BD3A0Light* light, f32 x, f32 y, f32 z) {
    light->posX = x;
    light->posY = y;
    light->posZ = z;
}

// .text:0x800BD3CC size:0x20
void LITInitAttn(Gap800BD3A0Light* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2) {
    GXInitLightAttn(light, a0, a1, a2, k0, k1, k2);
}

// .text:0x800BD3EC size:0x8C
void LITAlloc(Gap800BD3A0Light** out) {
    *out = _OSAllocFromHeap(32, sizeof(Gap800BD3A0Light));
    (*out)->posZ = 0.0f;
    (*out)->posY = 0.0f;
    (*out)->posX = 0.0f;
    (*out)->dirY = 0.0f;
    (*out)->dirX = 0.0f;
    (*out)->dirZ = 1.0f;
    (*out)->unkB8 = 0;
    (*out)->unkBC = 0;
    (*out)->unk74 = 0;
}

// .text:0x800BD478 size:0xD0
/* Applies the active render state to visible display objects referenced by the table. */
void fn_800BD478(GapBD478Source* source, GapBD478Table* table) {
    GapBD478Record* record;
    s32 j;
    s32 i;
    struct Gap800B993CObj* display;
    for (i = 0; i < table->count; i++) {
        record = &table->records[i];
        if (record->flags & GAPBD478_FLAGS_UNK_0x18) {
            for (j = 0; j < source->list->count; j++) {
                if (source->list->objects[j]->id == record->objectId) {
                    if (record->index == GAPBD478_INDEX_NONE) {
                        break;
                    }
                    display = source->list->objects[j]->display;
                    if (display != NULL) {
                        fn_800BC824(display, fn_800BF068()->unk_0x08);
                    }
                    break;
                }
            }
        }
    }
}

// .text:0x800BD548 size:0x128
/* Stores up to eight light pointers in the actor animation slot. */
void fn_800BD548(StadiumAnimEntry* slots, u8 count, ...) {
    va_list args;
    s32 i;
    Gap800BD3A0Light* light;

    slots->lightCount = count;
    va_start(args, count);
    for (i = 1; i <= count; i++) {
        light = va_arg(args, Gap800BD3A0Light*);
        switch (i) {
        case 1: slots->lights[0] = light; break;
        case 2: slots->lights[1] = light; break;
        case 3: slots->lights[2] = light; break;
        case 4: slots->lights[3] = light; break;
        case 5: slots->lights[4] = light; break;
        case 6: slots->lights[5] = light; break;
        case 7: slots->lights[6] = light; break;
        case 8: slots->lights[7] = light; break;
        }
    }
    va_end(args);
}

// .text:0x800BD670 size:0x254
/* Draws active stadium actors with their configured lights. */
void fn_800BD670(StadiumAnimTable* table, Mtx viewMtx) {
    u16 i;
    StadiumAnimTable* row;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);

    for (i = 0; i < table->count; i++) {
        GameActor* actor;
        StadiumAnimEntry* entry;
        /* FAKEMATCH: retain the table base while forming the slot pointer. */
        row = (StadiumAnimTable*)((StadiumAnimEntry*)table + i);
        entry = &row->entries[0];
        actor = entry->anim.actor;
        if (actor != NULL && row->entries[0].enabled) {
            if (entry->anim.onDraw != NULL) {
                entry->anim.onDraw(&entry->anim);
            }
            switch (entry->lightCount) {
            case 0: fn_800B3A78(actor, viewMtx, 0); break;
            case 1: fn_800B3A78(actor, viewMtx, 1, entry->lights[0]); break;
            case 2: fn_800B3A78(actor, viewMtx, 2, entry->lights[0], entry->lights[1]); break;
            case 3: fn_800B3A78(actor, viewMtx, 3, entry->lights[0], entry->lights[1], entry->lights[2]); break;
            case 4: fn_800B3A78(actor, viewMtx, 4, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3]); break;
            case 5: fn_800B3A78(actor, viewMtx, 5, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3], entry->lights[4]); break;
            case 6: fn_800B3A78(actor, viewMtx, 6, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3], entry->lights[4], entry->lights[5]); break;
            case 7: fn_800B3A78(actor, viewMtx, 7, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3], entry->lights[4], entry->lights[5], entry->lights[6]); break;
            case 8: fn_800B3A78(actor, viewMtx, 8, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3], entry->lights[4], entry->lights[5], entry->lights[6], entry->lights[7]); break;
            }
        }
    }
}

// .text:0x800BD8C4 size:0x160
/* Applies pending animation changes to each active stadium actor, then updates visibility. */
void fn_800BD8C4(struct HugeAnimCtrlObj* rawTable, Mtx viewMtx) {
    /* FAKEMATCH: declaration order steers registers; rows are addressed from the table base so
       the 0x34 header offset stays in each field displacement */
    GameActor* actor;
    StadiumAnimTable* row;
    StadiumAnimTable* table = (StadiumAnimTable*)rawTable;
    u16 i;

    for (i = 0; i < table->count; i++) {
        row = (StadiumAnimTable*)((StadiumAnimEntry*)table + i);
        if (row->entries[0].anim.actor != NULL) {
            u8 loopFlags;
            if (row->entries[0].anim.playAnim) {
                ACTSetAnimation(row->entries[0].anim.actor, row->entries[0].anim.bank, NULL, row->entries[0].anim.seqNum, 0.0f, row->entries[0].anim.startTime);
            }
            if (row->entries[0].anim.setTime) {
                fn_800B4CA0(row->entries[0].anim.actor, row->entries[0].anim.time);
            }
            if (row->entries[0].anim.setSpeed) {
                fn_800B4C04(row->entries[0].anim.actor, row->entries[0].anim.speed);
            }
            loopFlags = row->entries[0].anim.loopFlags;
            if (loopFlags & 2) {
                u8 loop = loopFlags & 1; /* FAKEMATCH: temp computes the loop bit before the actor load */
                fn_800B4AFC(row->entries[0].anim.actor, loop);
            }
            Set_FUN_800b2b6c(row->entries[0].anim.actor, row->entries[0].anim.unk68);

            if (row->entries[0].enabled) {
                actor = row->entries[0].anim.actor;
                memcpy(&((Gap800BD3A0ActorObj*)actor)->transform, &row->entries[0].anim.worldControl, sizeof(ControlExt));
                fn_800B2BFC((Gap800BD3A0ActorObj*)row->entries[0].anim.actor, row->entries[0].anim.unk64, row->entries[0].anim.unk66);
                AnimateActorBones((Gap800BD3A0ActorObj*)actor);
                fn_800B3F20((Gap800BD3A0ActorObj*)actor);
                fn_800B313C((Gap800BD3A0ActorObj*)actor);
            }

            actor = row->entries[0].anim.actor;
            actor->unk98 = (actor->unk98 & 0xFC) /* keep all but the two visibility bits */ | fn_800B3C04(0, actor, viewMtx);
            row->entries[0].anim.playAnim = 0;
            row->entries[0].anim.setTime = 0;
            row->entries[0].anim.setSpeed = 0;
            row->entries[0].anim.loopFlags &= 1;
        }
    }
}

// .text:0x800BDA24 size:0x70
void fn_800BDA24(Gap800BD3A0Instance* inst) {
    Gap800BD3A0ActorObj* obj = inst->obj;
    memcpy(&inst->obj->transform, &inst->transform, sizeof(Gap800BD3A0Transform));
    fn_800B2BFC(inst->obj, inst->unk64, inst->unk66);
    AnimateActorBones(obj);
    fn_800B3F20(obj);
    fn_800B313C(obj);
}

// .text:0x800BDA94 size:0x1F4
/* Draws one stadium actor with its configured lights. */
void fn_800BDA94(StadiumAnimEntry* entry, Mtx viewMtx) {
    GameActor* actor = entry->anim.actor;
    if (entry->anim.onDraw != NULL) {
        entry->anim.onDraw(&entry->anim);
    }
    switch (entry->lightCount) {
    case 0: fn_800B3A78(actor, viewMtx, 0); break;
    case 1: fn_800B3A78(actor, viewMtx, 1, entry->lights[0]); break;
    case 2: fn_800B3A78(actor, viewMtx, 2, entry->lights[0], entry->lights[1]); break;
    case 3: fn_800B3A78(actor, viewMtx, 3, entry->lights[0], entry->lights[1], entry->lights[2]); break;
    case 4: fn_800B3A78(actor, viewMtx, 4, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3]); break;
    case 5: fn_800B3A78(actor, viewMtx, 5, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3], entry->lights[4]); break;
    case 6: fn_800B3A78(actor, viewMtx, 6, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3], entry->lights[4], entry->lights[5]); break;
    case 7: fn_800B3A78(actor, viewMtx, 7, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3], entry->lights[4], entry->lights[5], entry->lights[6]); break;
    case 8: fn_800B3A78(actor, viewMtx, 8, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3], entry->lights[4], entry->lights[5], entry->lights[6], entry->lights[7]); break;
    }
}

// .text:0x800BDC88 size:0xEC
/* Not matched: best attempt and the remaining copy issue are in .agent/attempts/fn_800BDC88.c. */
void fn_800BDC88(StadiumAnimTable* table, s32 slot, u16 index, struct Gap800B117CRequest* request, ANIMBank* bank, s32 actorValue) {
}

// .text:0x800BDD74 size:0x118
/* Allocates and initializes a table of stadium actor animation entries. */
StadiumAnimTable* ActorObjectInitTable(u16 count) {
    StadiumAnimTable* table;
    u16 i;

    if (count == 0) {
        OSReport(lbl_800E7FC8);
        return NULL;
    }

    table = (StadiumAnimTable*)_OSAllocFromHeap(0x20, count * sizeof(StadiumAnimEntry) + sizeof(StadiumAnimTable) - sizeof(StadiumAnimEntry));
    table->count = count;
    PSMTXIdentity(table->identity);

    for (i = 0; i < table->count; i++) {
        table->entries[i].anim.actor = NULL;
        table->entries[i].anim.bank = NULL;
        table->entries[i].anim.onDraw = NULL;
        table->entries[i].anim.seqNum = 0;
        table->entries[i].anim.speed = 1.0f;
        table->entries[i].anim.time = 0.0f;
        table->entries[i].anim.startTime = 0.0f;
        table->entries[i].anim.unk64 = 0;
        table->entries[i].anim.unk66 = 0;
        table->entries[i].anim.unk68 = 0;
        table->entries[i].lightCount = 0;
        table->entries[i].lights[0] = NULL;
        table->entries[i].lights[1] = NULL;
        table->entries[i].lights[2] = NULL;
        table->entries[i].lights[3] = NULL;
        table->entries[i].lights[4] = NULL;
        table->entries[i].lights[5] = NULL;
        table->entries[i].lights[6] = NULL;
        table->entries[i].lights[7] = NULL;
        table->entries[i].anim.index = 0;
        table->entries[i].enabled = 0;
        table->entries[i].anim.playAnim = 0;
        table->entries[i].anim.setSpeed = 0;
        table->entries[i].anim.setTime = 0;
        table->entries[i].anim.loopFlags = 1;
        table->entries[i].anim.worldControl.control.type = 0;
        table->entries[i].anim.index = i;
    }
    return table;
}

// .text:0x800BDE8C size:0x14
void fn_800BDE8C(u8 value) {
    lbl_803009F8.unk4C = (value & 7) << 5;
}

// .text:0x800BDEA0 size:0xD0
/* Copies the current frame into the shadow texture and resets its bounds. */
void fn_800BDEA0(void) {
    if (lbl_803009F8.drawShadows) {
        if (lbl_803009F8.preCopy != NULL) {
            lbl_803009F8.preCopy(&lbl_803009F8.entries->data, 0);
        }
        GXSetTexCopySrc(0, 0, 640, 448);
        GXSetTexCopyDst(640, 480, GX_CTF_R4, GX_FALSE);
        GXCopyTex(*lbl_803009F8.texBuffer, GX_TRUE);
        GXPixModeSync();
        lbl_803009F8.boundCount = 0;
        lbl_803009F8.minX = lbl_803009F8.minY = lbl_803009F8.minZ = 100000000.0f;
        lbl_803009F8.maxX = lbl_803009F8.maxY = lbl_803009F8.maxZ = -100000000.0f;
        lbl_803009F8.x = lbl_803009F8.y = lbl_803009F8.z = 0.0f;
    }
}

// .text:0x800BDF70 size:0x70
void fn_800BDF70(Gap800BD3A0Model* model) {
    if (lbl_803009F8.drawShadows && lbl_803009F8.callback != NULL && model->unk6C) {
        u8 flags = model->actor->flags98;
        if ((flags & 0x24) && (flags & 0x12)) {
            lbl_803009F8.callback(model, &lbl_803009F8.entries->data);
        }
    }
}

// .text:0x800BDFE0 size:0xBC
void fn_800BDFE0(void) {
    return;
}

// .text:0x800BE09C size:0xBC
void fn_800BE09C(void) {
    return;
}

// .text:0x800BE158 size:0x340
void fn_800BE158(void) {
    return;
}

// .text:0x800BE498 size:0x56C
void fn_800BE498(void) {
    return;
}

// .text:0x800BEA04 size:0x138
void fn_800BEA04(void) {
    return;
}

// .text:0x800BEB3C size:0x44
void fn_800BEB3C(void) {
    lbl_803009F8.boundCount = 0;
    lbl_803009F8.minX = lbl_803009F8.minY = lbl_803009F8.minZ = 100000000.0f;
    lbl_803009F8.maxX = lbl_803009F8.maxY = lbl_803009F8.maxZ = -100000000.0f;
    lbl_803009F8.x = lbl_803009F8.y = lbl_803009F8.z = 0.0f;
}

// .text:0x800BEB80 size:0x20
u8* fn_800BEB80(u8 index) {
    return &lbl_803009F8.entries[index].unkB0;
}

// .text:0x800BEBA0 size:0x10
u8 fn_800BEBA0(void) {
    return lbl_803009F8.drawShadows;
}

// .text:0x800BEBB0 size:0x10
u8 GetDrawShadows(void) {
    return lbl_803009F8.drawShadows;
}

// .text:0x800BEBC0 size:0xC
void DrawShadows(u8 enable) {
    lbl_803009F8.drawShadows = enable;
}

// .text:0x800BEBCC size:0x34
void fn_800BEBCC(void) {
    return;
}

// .text:0x800BEC00 size:0x30
void fn_800BEC00(BOOL enable) {
    if (enable) lbl_803009F8.unk4D = -1;
    else lbl_803009F8.unk4D = 1;
}

// .text:0x800BEC30 size:0x3D8
void fn_800BEC30(void) {
    return;
}

// .text:0x800BF008 size:0x30
void fn_800BF008(void) {
    GXLoadTlut(lbl_803009F8.tlut, 15);
}

// .text:0x800BF038 size:0x10
void fn_800BF038(void (*preCopy)(Gap800BD3A0EntryData* data, s32 arg)) {
    lbl_803009F8.preCopy = preCopy;
}

// .text:0x800BF048 size:0x10
void fn_800BF048(s32 value) {
    lbl_803009F8.unk18 = value;
}

// .text:0x800BF058 size:0x10
void fn_800BF058(Gap800BD3A0Callback value) {
    lbl_803009F8.callback = value;
}

// .text:0x800BF068 size:0xC
Gap800BD3A0State* fn_800BF068(void) {
    return &lbl_803009F8;
}

// .text:0x800BF074 size:0x130
void SKNLoadFile(void) {
    return;
}

// .text:0x800BF1A4 size:0x1C
void SKNFlushByIndex1(void) {
    return;
}

// .text:0x800BF1C0 size:0x28
void SKNFlushByIndex2(void) {
    return;
}

// .text:0x800BF1E8 size:0x1C
void SKNBzero32B(void) {
    return;
}

// .text:0x800BF204 size:0xA4
void SKNInit(void) {
    return;
}

// .text:0x800BF2A8 size:0x5F4
void fn_800BF2A8(void) {
    return;
}

// .text:0x800BF89C size:0x5F4
void SKNIt(void) {
    return;
}

// .text:0x800BFE90 size:0x10C
void SKN1Vecs16Norms16(void) {
    return;
}

// .text:0x800BFF9C size:0x10C
void fn_800BFF9C(void) {
    return;
}

// .text:0x800C00A8 size:0x220
void SKN2Vecs16Norms16NoTouch(void) {
    return;
}

// .text:0x800C02C8 size:0x220
void fn_800C02C8(void) {
    return;
}

// .text:0x800C04E8 size:0x148
void SKNAccVecs16Norms16Iu161(void) {
    return;
}

// .text:0x800C0630 size:0x140
void SKNAccVecs16Norms16Iu162(void) {
    return;
}

// .text:0x800C0770 size:0x4C
void convertTextureHeader(TextureArchiveHeader* hdr) {
    s32 i;

    for (i = 0; i < hdr->count; i++) {
        TextureHeader* t = &hdr->textures[i];
        if (t->dataOffset != 0) {
            t->dataOffset = (u32)hdr + t->dataOffset;
        }
        if (t->clutOffset != 0) {
            t->clutOffset = (u32)hdr + t->clutOffset;
        }
        t->texId = i;
    }
}

// .text:0x800C07BC size:0x2D0
void fn_800C07BC(void) {
    return;
}
