#include "challenge/rep_74A0.h"
#include "Dolphin/gx.h"
#include "Dolphin/GX/GXHardware.h"
/* rep_0138.h uses a conflicting light type; preserve its projection API here. */
void C_MTXFrustum(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void fn_800B806C(s32 index, f32 t, f32 b, f32 l, f32 r, f32 nearZ, f32 farZ, f32 scale);
#include "Dolphin/GX/GXTransform.h"
typedef struct ChallengeProjectionState {
    Mtx view;
    u8 _pad30[0xC];
    Vec position;
    Vec direction;
} ChallengeProjectionState;
extern ChallengeProjectionState lbl_1_bss_6B7C;
/* The light owning header conflicts with this unit's actor and allocator
   declarations; these forward declarations preserve its light API types. */
typedef struct Gap800BD3A0Light Gap800BD3A0Light;
typedef struct Gap800BD3A0Color { u8 r, g, b, a; } Gap800BD3A0Color;
void LITInitAttn(Gap800BD3A0Light*, f32, f32, f32, f32, f32, f32);
void LITInitPos(Gap800BD3A0Light*, f32, f32, f32);
void LITInitDir(Gap800BD3A0Light*, f32, f32, f32);
void LITAlloc(Gap800BD3A0Light**);
void LITInitColor(Gap800BD3A0Light*, Gap800BD3A0Color*);
void LITXForm(Gap800BD3A0Light*, Mtx);
typedef struct ChallengeLightPosition { Vec position; f32 unk_0x0C; } ChallengeLightPosition;
extern ChallengeLightPosition lbl_80367318[3];


// .text:0x000182C0 size:0x2BC
void fn_1_182C0(void) {
    return;
}

// .text:0x0001857C size:0x888
void fn_1_1857C(void) {
    return;
}

// .text:0x00018E04 size:0xE0
void fn_1_18E04(ChallengeOrbit* orbit, f32 angle) {
    f32 sine;
    f32 cosine;
    f32 radians = 0.017453292f * angle;
    sine = (f32)sin(radians);
    cosine = (f32)cos(radians);
    orbit->position.x = (sine * lbl_1_data_FB24.radius) / 100000.0f;
    orbit->position.y = (cosine * lbl_1_data_FB24.radius) / 100000.0f;
    orbit->position.z = 0.0f;
}

// .text:0x00018EE4 size:0x2F8
void fn_1_18EE4(ChallengeOrbit* orbit) {
    s32 minimum = lbl_1_data_FB24.colorMinimum;
    u32 base = (u8)minimum;
    u8 range;
    f32 sine, cosine, speed;
    f32 angle = 0.0f;
    orbit->origin.x = (f32)(orbit->index * 2) / lbl_1_data_FB24.unk0 - 1.0f;
    orbit->origin.y = -1.0f;
    orbit->origin.z = 50.0f * ((f32)rand() / 32767.0f) + 50.0f;
    sine = sin(angle);
    cosine = cos(angle);
    orbit->position.x = (sine * lbl_1_data_FB24.radius) / 100000.0f;
    orbit->position.y = (cosine * lbl_1_data_FB24.radius) / 100000.0f;
    orbit->position.z = 0;
    orbit->rotation.x = orbit->rotation.y = orbit->rotation.z = 0;
    speed = lbl_1_data_FB24.angularSpeed / 100000.0f;
    orbit->angularVelocity.x = speed * ((f32)rand() / 32767.0f);
    orbit->angularVelocity.y = speed * ((f32)rand() / 32767.0f);
    orbit->angularVelocity.z = speed * ((f32)rand() / 32767.0f);
    orbit->colors[0].a = orbit->colors[1].a = 255;
    range = 255 - minimum;
    orbit->colors[0].g = base + rand() % range;
    orbit->colors[0].b = base + rand() % range;
    orbit->colors[1].r = base + rand() % range;
    orbit->colors[1].g = base + rand() % range;
    orbit->colors[1].b = base + rand() % range;
}

// .text:0x000191DC size:0x3A0
void fn_1_191DC(void) {
    return;
}

// .text:0x0001957C size:0x3D0
void fn_1_1957C(void) {
    return;
}

// .text:0x0001994C size:0x3D0
void fn_1_1994C(void) {
    return;
}

// .text:0x00019D1C size:0x44
s32 fn_1_19D1C(u32 flags) {
    switch ((flags >> 4) & 0xF) {
    case 0:
    case 1:
        return 1;
    case 2:
    case 3:
        return 2;
    case 4:
        return 4;
    default:
        return 0;
    }
}

// .text:0x00019D60 size:0x48C
void fn_1_19D60(ChallengeRenderModel* model, s32 mode) {
    return;
}

// .text:0x0001A1EC size:0xA4
void fn_1_1A1EC(ChallengeRenderTask* task, s32 mode) {
    ChallengeRenderObject* object = task->object;
    if (task->callback != 0) {
        task->callback(task);
    }
    if (object->model != 0) {
        fn_800B2D5C(object);
        GXInvalidateVtxCache();
        fn_1_19D60(object->model, mode);
    } else {
        for (object = object->children; object != 0; object = object->next) {
            if (object->model != 0) {
                DOSetWorldMatrix(object->model, object->world);
            }
            fn_1_19D60(object->model, mode);
        }
    }
}

// .text:0x0001A290 size:0x124
static inline void drawChallengeTask(HugeAnimEntry68* entry, s32 mode) {
    ChallengeRenderTask* task = (ChallengeRenderTask*)&entry->unk34;
    ChallengeRenderObject* object = task->object;
    if (object != 0 && entry[1].unk10 != 0) {
    if (task->callback != 0) {
        task->callback(task);
    }
    if (object->model != 0) {
        fn_800B2D5C(object);
        GXInvalidateVtxCache();
        fn_1_19D60(object->model, mode);
    } else {
        for (object = object->children; object != 0; object = object->next) {
            if (object->model != 0) {
                DOSetWorldMatrix(object->model, object->world);
            }
            fn_1_19D60(object->model, mode);
        }
    }
    }
}

void fn_1_1A290(HugeAnimEntry68* entries, s32 mode) {
    u16 i;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < entries->count; i++) {
        drawChallengeTask(&entries[i], mode);
    }
}

// .text:0x0001A3B4 size:0x3C0
#include "game/sta_c4.h"
typedef struct ChallengePreviewTexture { StaC4TexDesc desc; u16 selected, reserved; } ChallengePreviewTexture;
typedef struct ChallengePreviewTextures {
    u16 count, reserved;
    ChallengePreviewTexture entries[1];
} ChallengePreviewTextures;
extern u8* lbl_1_bss_6AAC[24];
static inline ChallengePreviewTexture* selectedPreviewTexture(ChallengePreviewTextures* archive) {
    return &archive->entries[archive->entries[0].selected];
}
/* Load the selected texture archive and draw its preview quad. */
void fn_1_1A3B4(void) {
    GXTexObj texture;
    GXTlutObj palette;
    GXColor color = {255,255,255,255};
    ChallengePreviewTextures* archive = (ChallengePreviewTextures*)lbl_1_bss_6AAC[lbl_803CC1B8->flag14];
    ChallengePreviewTexture* entry;
    u32 count = archive->count;
    u32 i;
    {
    ChallengePreviewTexture* selected = selectedPreviewTexture(archive);
    u32 hasPalette = selected->desc.tlut != 0;
    entry = selected;
    if (hasPalette) {
        for (i = 0; i < count; entry++, i++) {
            GXInitTlutObj(&palette, entry->desc.tlut, entry->desc.tlutFormat, entry->desc.tlutEntries);
            GXLoadTlut(&palette, 0);
            GXInitTexObjCI(&texture, entry->desc.image, entry->desc.width, entry->desc.height, entry->desc.format, 0, 0, 0, 0);
            GXInitTexObjLOD(&texture, 0, 0, 0.0f, 0.0f, 0.0f, 0, 0, 0);
            GXLoadTexObj(&texture, 0);
        }
    } else {
        for (i = 0; i < count; entry++, i++) {
            GXInitTexObj(&texture, entry->desc.image, entry->desc.width, entry->desc.height, entry->desc.format, 0, 0, 0);
            GXInitTexObjLOD(&texture, 0, 0, 0.0f, 0.0f, 0.0f, 0, 0, 0);
            GXLoadTexObj(&texture, 0);
        }
    }
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevColor(1, color);
    GXSetTevColorIn(0, 15, 15, 15, 8);
    GXSetTevAlphaIn(0, 7, 7, 7, 1);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetBlendMode(0, 4, 5, 7);
    GXSetCullMode(0);
    GXLoadPosMtxImm(lbl_1_bss_6B7C.view, 0);
    GXSetCurrentMtx(0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = -3.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 20.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = -3.0f;
    GXWGFifo.f32 = -3.0f;
    GXWGFifo.f32 = 20.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = -3.0f;
    GXWGFifo.f32 = 20.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 20.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = 1.0f;
}

// .text:0x0001A774 size:0xDC
void fn_1_1A774(void) {
    s32 i;
    s32 r, g, b, a;
    ChallengeSelection* selection = &lbl_1_bss_69F0;
    hugeAnimStruct* animations = &g_hugeAnimStruct;
    Mtx matrix;
    ChallengeModelGroup* model = (ChallengeModelGroup*)animations->ctrlOrBonePtr[selection->group].unk34;
    if (selection->selected < model->count) {
        for (i = 0; i < ((ChallengeModelGroup*)animations->ctrlOrBonePtr[selection->group].unk34)->count; i++) {
            if (i == selection->selected) {
                r = 0; g = 255; b = 255; a = 255;
            } else {
                r = 0; g = 128; b = 128; a = 64;
            }
            fn_800B2C88((ChallengeModelGroup*)animations->ctrlOrBonePtr[selection->group].unk34, i, matrix);
            fn_1_1A850(matrix, selection->matrix, r, g, b, a);
        }
    }
}

// .text:0x0001A850 size:0x554
void fn_1_1A850(Mtx matrix, Mtx view, s32 r, s32 g, s32 b, s32 a) {
    return;
}

// .text:0x0001ADA4 size:0x294
/* Draw a unit-spaced green reference grid across the preview ground plane. */
void fn_1_1ADA4(void) {
    Mtx44 projection;
    s32 i;
    C_MTXFrustum(projection, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
    GXSetProjection(projection, GX_PERSPECTIVE);
    GXLoadPosMtxImm(lbl_1_bss_6B7C.view, 0);
    GXSetCurrentMtx(0);
    GXSetColorUpdate(GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    for (i = -24; i < 25; i++) {
        f32 coordinate = i;
        GXBegin(GX_LINES, GX_VTXFMT0, 4);
        GXWGFifo.f32 = -24.0f; GXWGFifo.f32 = 0.0f; GXWGFifo.f32 = coordinate;
        GXWGFifo.u8 = 0; GXWGFifo.u8 = 255; GXWGFifo.u8 = 0; GXWGFifo.u8 = 200;
        GXWGFifo.f32 = 24.0f; GXWGFifo.f32 = 0.0f; GXWGFifo.f32 = coordinate;
        GXWGFifo.u8 = 0; GXWGFifo.u8 = 255; GXWGFifo.u8 = 0; GXWGFifo.u8 = 200;
        GXWGFifo.f32 = coordinate; GXWGFifo.f32 = 0.0f; GXWGFifo.f32 = -24.0f;
        GXWGFifo.u8 = 0; GXWGFifo.u8 = 255; GXWGFifo.u8 = 0; GXWGFifo.u8 = 200;
        GXWGFifo.f32 = coordinate; GXWGFifo.f32 = 0.0f; GXWGFifo.f32 = 24.0f;
        GXWGFifo.u8 = 0; GXWGFifo.u8 = 255; GXWGFifo.u8 = 0; GXWGFifo.u8 = 200;
    }
}

// .text:0x0001B038 size:0xC4
/* FAKEMATCH: pass the colour by value to preserve the original temporary
   copy before calling the light API. */
static inline void setChallengeLightColor(Gap800BD3A0Light* light, Gap800BD3A0Color color) {
    LITInitColor(light, &color);
}
// Set up three white challenge lights and transform them into view space.
void fn_1_1B038(void) {
    Gap800BD3A0Color color = {255, 255, 255, 255};
    s32 i;
    for (i = 0; i < 3; i++) {
        LITInitAttn((Gap800BD3A0Light*)g_hugeAnimStruct.menuLights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        LITInitPos((Gap800BD3A0Light*)g_hugeAnimStruct.menuLights[i], lbl_80367318[i].position.x, lbl_80367318[i].position.y, lbl_80367318[i].position.z);
        setChallengeLightColor((Gap800BD3A0Light*)g_hugeAnimStruct.menuLights[i], color);
        LITXForm((Gap800BD3A0Light*)g_hugeAnimStruct.menuLights[i], lbl_1_bss_69FC.lightMatrix);
    }
}

// .text:0x0001B0FC size:0x1CC
/* Allocate and initialize the three challenge lights and their default colors. */
void fn_1_1B0FC(void) {
    Gap800BD3A0Color white = {255, 255, 255, 255};
    Gap800BD3A0Color blue = {0, 0, 255, 255};
    Gap800BD3A0Light** first = (Gap800BD3A0Light**)&g_hugeAnimStruct.menuLights[0];
    Gap800BD3A0Light** second;
    Gap800BD3A0Light** third;
    LITAlloc(first);
    second = (Gap800BD3A0Light**)&g_hugeAnimStruct.menuLights[1];
    LITAlloc(second);
    third = (Gap800BD3A0Light**)&g_hugeAnimStruct.menuLights[2];
    LITAlloc(third);
    LITInitAttn(*first, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(*first, -100.0f, -100.0f, 100.0f);
    setChallengeLightColor(*first, white);
    LITInitAttn(*second, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(*second, 500.0f, -500.0f, 250.0f);
    setChallengeLightColor(*second, blue);
    LITInitAttn(*third, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(*third, 0.0f, -500.0f, 250.0f);
    setChallengeLightColor(*third, blue);
    LITInitDir(*first, 100.0f, 100.0f, -100.0f);
}

// .text:0x0001B2C8 size:0x15C
void fn_1_1B2C8(void) {
    return;
}

// .text:0x0001B424 size:0x298
void fn_1_1B424(void) {
    return;
}

// .text:0x0001B6BC size:0x120
/* Set the challenge camera pose and perspective/overlay projection volumes. */
void fn_1_1B6BC(void) {
    Mtx44 projection;
    lbl_1_bss_6B7C.direction.x = 0.0f;
    lbl_1_bss_6B7C.direction.y = -0.8f;
    lbl_1_bss_6B7C.direction.z = 0.0f;
    lbl_1_bss_6B7C.position.x = 0.0f;
    lbl_1_bss_6B7C.position.y = 0.0f;
    lbl_1_bss_6B7C.position.z = 10.0f;
    C_MTXFrustum(projection, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_800B806C(0, -240.0f, 240.0f, -320.0f, 320.0f, -512.0f, -1.0f, 1280.0f);
}

// .text:0x0001B7DC size:0xBF0
void fn_1_1B7DC(void) {
    return;
}

// .text:0x0001C3CC size:0x4F4
void fn_1_1C3CC(void) {
    return;
}

// .text:0x0001C8C0 size:0x324
typedef union ChallengeModelSection { u32 offset; u8* data; } ChallengeModelSection;
struct MenusAnimationAux { ChallengeModelSection sections[5]; };
typedef struct ChallengeModelCallback {
    u8 _pad0[0x3C];
    void (*callback)(Rep74A0Obj*);
} ChallengeModelCallback;
extern u8 lbl_1_bss_6A94[24];
extern u8* lbl_1_bss_6AAC[24];
HugeAnimEntry68* ActorObjectInitTable(u16 count);
void ANIMGet(AnimSlotTable* bank);
void convertTextureHeader(u8* texture);
void LoadActorLayout(u8* layout);
void convertGeometryAndSknHeader(u8* geometry, u8* skin);
void fn_800BCE38(u8* geometry);
void haveActLayoutPointToGeoHeader(u8* layout, u8* geometry);
void fn_800BD190(u8* geometry, u8* texture);
void fn_800BDC88(HugeAnimEntry68* entries, u16 slot, u16 index, u8* layout, AnimSlotTable* bank, u8* skin);
void fn_800B2C08(AnimLevel1* model, s32 mode);
void fn_1_1C8C0(void) {
    u32 i;
    u8* layout;
    u8* skin;
    g_hugeAnimStruct.ctrlOrBonePtr = ActorObjectInitTable(24);
    for (i = 0; i < 24; i++) {
        ActRelatedSub* playback;
        AnimSlotTable* bank;
        if (i < 24) {
            struct MenusAnimationAux* archive = g_hugeAnimStruct.fielderStructs[i].aux;
            u8* geometry;
            u8* texture;
            if (lbl_1_bss_6A94[i]) {
                u32 j;
                for (j = 0; j < 5; j++) {
                    if (j == 4) {
                        g_hugeAnimStruct.fielderStructs[i].slots[0] = (AnimSlotTable*)((u8*)archive + archive->sections[j].offset);
                        ANIMGet(g_hugeAnimStruct.fielderStructs[i].slots[0]);
                    } else {
                        g_hugeAnimStruct.fielderStructs[i].aux->sections[j].data = (u8*)archive + archive->sections[j].offset;
                    }
                }
            } else {
                g_hugeAnimStruct.fielderStructs[i].aux->sections[0].data = (u8*)archive + archive->sections[0].offset;
                g_hugeAnimStruct.fielderStructs[i].aux->sections[1].data = (u8*)archive + archive->sections[1].offset;
                g_hugeAnimStruct.fielderStructs[i].aux->sections[2].data = (u8*)archive + archive->sections[2].offset;
            }
            texture = g_hugeAnimStruct.fielderStructs[i].aux->sections[0].data;
            geometry = g_hugeAnimStruct.fielderStructs[i].aux->sections[1].data;
            layout = g_hugeAnimStruct.fielderStructs[i].aux->sections[2].data;
            skin = lbl_1_bss_6A94[i] ? g_hugeAnimStruct.fielderStructs[i].aux->sections[3].data : NULL;
            convertTextureHeader(texture);
            LoadActorLayout(layout);
            if (lbl_1_bss_6A94[i]) convertGeometryAndSknHeader(geometry, skin);
            else fn_800BCE38(geometry);
            lbl_1_bss_6AAC[i] = texture;
            haveActLayoutPointToGeoHeader(layout, geometry);
            fn_800BD190(geometry, texture);
        }
        {
            AnimationStruct* actor;
            bank = lbl_1_bss_6A94[i] ? g_hugeAnimStruct.fielderStructs[i].slots[0] : NULL;
            actor = &g_hugeAnimStruct.fielderStructs[i];
            fn_800BDC88(g_hugeAnimStruct.ctrlOrBonePtr, (u16)i, (u16)i, layout,
                bank, skin);
            fn_800BD548(&((HugeAnimCtrlEntry*)g_hugeAnimStruct.ctrlOrBonePtr)[i].sub34, 3,
                g_hugeAnimStruct.menuLights[0], g_hugeAnimStruct.menuLights[1], g_hugeAnimStruct.menuLights[2], g_hugeAnimStruct.menuLights[3]);
            CTRLSetTranslation(&((HugeAnimCtrlEntry*)g_hugeAnimStruct.ctrlOrBonePtr)[i].ctrl, 0, 0, 0);
            CTRLSetRotation(&((HugeAnimCtrlEntry*)g_hugeAnimStruct.ctrlOrBonePtr)[i].ctrl, 0, 0, 0);
            playback = &((ActRelatedEntry*)g_hugeAnimStruct.ctrlOrBonePtr)[i].sub;
            playback->float54 = 0.5f;
            playback->flag5a = 1;
            g_hugeAnimStruct.ctrlOrBonePtr[i].unk34->animFlags |= 4;
            if (i == 1) fn_800B2C08(g_hugeAnimStruct.ctrlOrBonePtr[i].unk34, 0);
            else fn_800B2C08(g_hugeAnimStruct.ctrlOrBonePtr[i].unk34, 1);
            actor->ring = (AnimRingInfo*)g_hugeAnimStruct.ctrlOrBonePtr[i].unk34;
            actor->unk34.x = 0; actor->unk34.y = 0; actor->unk34.z = 10;
            actor->previewScale = 0.5f;
            actor->unk_25D = i == 0;
            ((ChallengeModelCallback*)&g_hugeAnimStruct.ctrlOrBonePtr[i])->callback = fn_1_1D0E8;
        }
    }
    lbl_803CC1B8->aFunctionPointer = fn_1_1C3CC;
}

// .text:0x0001CBE4 size:0x504
void fn_1_1CBE4(void) {
    return;
}

// .text:0x0001D0E8 size:0x24
void fn_1_1D0E8(Rep74A0Obj* obj) {
    fn_800B9AA8(obj->context);
}

// .text:0x0001D10C size:0x4
void fn_1_1D10C(void) {
    return;
}

// .text:0x0001D110 size:0x340
void fn_1_1D110(void) {
    return;
}

// .text:0x0001D450 size:0x20
void fn_1_1D450(void) {
    fn_1_1CBE4();
}

// .text:0x0001D470 size:0xA4
void fn_1_1D470(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 i;

    for (i = 0; i < 0x18; i++) {
        lbl_1_bss_69FC.flags[i] = 0;
    }
    scene->flag15 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_1_1D450;
}

// .text:0x0001D514 size:0x7C
void fn_1_1D514(void) {
    return;
}
