#include "Unknown/gap_800B993C.h"

// .text:0x800B993C size:0xC
void fn_800B993C(void) {
    lbl_803CC200 = 0x0;
}

// .text:0x800B9948 size:0x8
void fn_800B9948(s32 value) {
    lbl_803CC200 = value;
}

// .text:0x800B9950 size:0x1C
void fn_800B9950(u32 flags, f32 a, f32 b) {
    if (flags & 1) {
        lbl_803CC1F8 = a;
    }
    if (flags & 2) {
        lbl_803CC1FC = b;
    }
}

// .text:0x800B996C size:0x8
void fn_800B996C(s32 value) {
    lbl_803CC1F4 = value;
}

// .text:0x800B9974 size:0x50
void SetFogNone(void) {
    Gap800B993CColor color;
    color.r = color.g = color.b = 0;
    GXSetFog(0, 0.0f, 0.0f, 0.0f, 0.0f, color);
}

// .text:0x800B99C4 size:0x6C
void SetFog(void) {
    return;
}

// .text:0x800B9A30 size:0x6C
void SetFogNoneAgain(void) {
    lbl_80111700.color.r = lbl_80111700.color.g = lbl_80111700.color.b = 0;
    lbl_80111700.type = 0;
    lbl_80111700.start = 0.0f;
    lbl_80111700.end = 0.0f;
    lbl_80111700.nearZ = 0.0f;
    lbl_80111700.farZ = 0.0f;
    GXSetFog(0, 0.0f, 0.0f, 0.0f, 0.0f, lbl_80111700.color);
}

// .text:0x800B9A9C size:0xC
void fn_800B9A9C(s32 a, f32 b) {
    lbl_803CC21C = a;
    lbl_803CC218 = b;
}

// .text:0x800B9AA8 size:0x8
void fn_800B9AA8(s32 value) {
    lbl_803CC1F0 = value;
}

// .text:0x800B9AB0 size:0x3F8
void fn_800B9AB0(void) {
    return;
}

// .text:0x800B9EA8 size:0x5A4
void fn_800B9EA8(void) {
    return;
}

// .text:0x800BA44C size:0x3FC
void fn_800BA44C(void) {
    return;
}

// .text:0x800BA848 size:0x12E4
void Custom_SetState(void) {
    return;
}

// .text:0x800BBB2C size:0x430
void SetState(void) {
    return;
}

// .text:0x800BBF5C size:0x168
void GetColorFromQuant(void) {
    return;
}

// .text:0x800BC0C4 size:0x724
// TODO: remove pragma once LoadGeoPalette is decompiled (keeps stub from inlining)
#pragma dont_inline on
void DOVARender(Gap800B993CObj* obj, f32 matrix[3][4], u32 a, u32 b) {
    return;
}

#pragma dont_inline reset

// .text:0x800BC7E8 size:0x3C
void DOVARenderSkin(Gap800B993CObj* obj, f32 matrix[3][4], f32 skinMatrices[][3][4], u16* indices, u32 a, u32 b) {
    lbl_803CC204 = skinMatrices;
    lbl_803CC208 = indices;
    DOVARender(obj, matrix, a, b);
    lbl_803CC204 = NULL;
    lbl_803CC208 = NULL;
}

// .text:0x800BC824 size:0x10
void fn_800BC824(Gap800B993CObj* obj, s32 value) {
    if (obj != NULL) {
        obj->unk50 = value;
    }
}

// .text:0x800BC834 size:0x2C
void DOSetWorldMatrix(Gap800B993CObj* obj, f32 matrix[3][4]) {
    PSMTXCopy(matrix, obj->worldMatrix);
}

// .text:0x800BC860 size:0x258
#pragma dont_inline on
void InitDisplayObjWithLayout(Gap800B993CObj* obj, Gap800B993CPart* part) {
    return;
}
#pragma dont_inline reset

// .text:0x800BCAB8 size:0x8C
void DOGet(Gap800B993CObj** out, Gap800B993CModel* model, u16 index) {
    Gap800B993CPart* part;
    if (index >= model->count) {
        OSReport(lbl_800E7F8C, index, model->count);
        *out = NULL;
    } else {
        part = model->parts[index].part;
        *out = _OSAllocFromHeap(32, sizeof(Gap800B993CObj));
        InitDisplayObjWithLayout(*out, part);
    }
}

// .text:0x800BCB44 size:0x21C
// TODO: remove pragma once LoadGeoPalette is decompiled (keeps stub from inlining)
#pragma dont_inline on
Gap800B993CGeo* LoadGeoPalette(Gap800B993CGeoFile* file) {
    GeoPaletteHdr* pal = (GeoPaletteHdr*)file;
    u32 ret = 0;
    GeoDescriptor* desc;
    GeoLayout* layout;
    GeoRelocArray* arr;
    GeoTextureData* tex;
    GeoDisplayData* disp;
    GeoDisplayStateList* states;
    u16 i;
    u16 j;

    if (pal->userDataSize != 0 && pal->userData != 0) {
        pal->userData = pal->userData + (u32)pal;
    }
    pal->descriptorArray = pal->descriptorArray + (u32)pal;
    for (i = 0; i < pal->numDescriptors; i++) {
        desc = (GeoDescriptor*)pal->descriptorArray;
        desc[i].layout = desc[i].layout + (u32)pal;
        desc = (GeoDescriptor*)pal->descriptorArray;
        desc[i].name = desc[i].name + (u32)pal;
        layout = (GeoLayout*)((GeoDescriptor*)pal->descriptorArray)[i].layout;
        if (layout->positionData != 0) {
            layout->positionData = layout->positionData + (u32)layout;
            arr = (GeoRelocArray*)layout->positionData;
            if (arr->array != 0) {
                arr->array = arr->array + (u32)layout;
            }
            arr = (GeoRelocArray*)layout->positionData;
            if (arr->compCount == 6) {
                ret = arr->array;
            }
        }
        if (layout->colorData != 0) {
            layout->colorData = layout->colorData + (u32)layout;
            arr = (GeoRelocArray*)layout->colorData;
            if (arr->array != 0) {
                arr->array = arr->array + (u32)layout;
            }
        }
        if (layout->textureData != 0) {
            layout->textureData = layout->textureData + (u32)layout;
            for (j = 0; j < layout->numTextureChannels; j++) {
                tex = (GeoTextureData*)layout->textureData;
                if (tex[j].textureCoordArray != 0) {
                    tex[j].textureCoordArray = (u32)layout + tex[j].textureCoordArray;
                }
                tex = (GeoTextureData*)layout->textureData;
                if (tex[j].texturePaletteName != 0) {
                    tex[j].texturePaletteName = (u32)layout + tex[j].texturePaletteName;
                }
            }
        }
        if (layout->lightingData != 0) {
            layout->lightingData = layout->lightingData + (u32)layout;
            arr = (GeoRelocArray*)layout->lightingData;
            if (arr->array != 0) {
                arr->array = arr->array + (u32)layout;
            }
        }
        if (layout->displayData != 0) {
            layout->displayData = layout->displayData + (u32)layout;
            disp = (GeoDisplayData*)layout->displayData;
            if (disp->primitiveBank != 0) {
                disp->primitiveBank = disp->primitiveBank + (u32)layout;
            }
            disp = (GeoDisplayData*)layout->displayData;
            if (disp->displayStateList != 0) {
                disp->displayStateList = disp->displayStateList + (u32)layout;
            }
            for (j = 0; j < ((GeoDisplayData*)layout->displayData)->numStateEntries; j++) {
                states = (GeoDisplayStateList*)((GeoDisplayData*)layout->displayData)->displayStateList;
                if (states[j].primitiveList != 0) {
                    states[j].primitiveList = (u32)layout + states[j].primitiveList;
                }
            }
        }
        if (layout->unk18 != 0) {
            layout->unk18 = layout->unk18 + (u32)layout;
        }
    }
    return (Gap800B993CGeo*)ret;
}
#pragma dont_inline reset

// .text:0x800BCD60 size:0x5C
void convertGeometryAndSknHeader(Gap800B993CGeoFile* file, Gap800B993CSkin* skin) {
    Gap800B993CGeo* geo = LoadGeoPalette(file);
    if (skin != NULL) {
        SKNLoadFile(skin, geo);
    }
    file->geo = geo;
}

// .text:0x800BCDBC size:0x7C
void fn_800BCDBC(Gap800B993CModel* model) {
    s32 i;
    for (i = model->count - 1; i >= 0; i--) {
        if (model->parts[i].part->entries != NULL) {
            fn_800ACFB0((Gap800B993CAllocation*)model->parts[i].part->entries);
        }
    }
    fn_800ACFB0((Gap800B993CAllocation*)model->parts[0].part);
}

// .text:0x800BCE38 size:0xC0
void fn_800BCE38(void) {
    return;
}

// .text:0x800BCEF8 size:0x298
void fn_800BCEF8(void) {
    return;
}

// .text:0x800BD190 size:0x58
void fn_800BD190(Gap800B993CModel* model, u32 value) {
    u32 i;
    s32 j;
    for (i = 0; i < model->count; i++) {
        for (j = 0; j < model->parts[i].part->count; j++) {
            model->parts[i].part->entries[j].value = value;
        }
    }
}

// .text:0x800BD1E8 size:0x8
void fn_800BD1E8(s32 value) {
    lbl_803CC20C = value;
}

// Set quantization register 5 for paired-single loads and stores.
// .text:0x800BD1F0 size:0x8
asm void __MTGQR5(register u32 value) {
    nofralloc
    mtspr GQR5, value
    blr
}

// Set quantization register 6 for paired-single loads and stores.
// .text:0x800BD1F8 size:0x8
asm void __MTGQR6(register u32 value) {
    nofralloc
    mtspr GQR6, value
    blr
}

// Set quantization register 7 for paired-single loads and stores.
// .text:0x800BD200 size:0x8
asm void __MTGQR7(register u32 value) {
    nofralloc
    mtspr GQR7, value
    blr
}

// .text:0x800BD208 size:0x38
void GQRSetup7(void) {
    return;
}

// .text:0x800BD240 size:0x38
void GQRSetup6(void) {
    return;
}

// .text:0x800BD278 size:0x38
void GQRSetup5(void) {
    return;
}

// .text:0x800BD2B0 size:0x1C
u8 fn_800BD2B0(Gap800B993CColor* out) {
    if (lbl_803CC220 != 0) {
        *out = lbl_803CC224;
    }
    return lbl_803CC220;
}

// .text:0x800BD2CC size:0x10
void fn_800BD2CC(u8 enable, Gap800B993CColor* color) {
    u32 value = color->word;
    lbl_803CC220 = enable;
    lbl_803CC224.word = value;
}

// .text:0x800BD2DC size:0x24
void fn_800BD2DC(void) {
    lbl_803CC220 = 0;
    lbl_803CC224.r = 0;
    lbl_803CC224.b = 0;
    lbl_803CC224.g = 0;
    lbl_803CC224.a = 0xFF;
}

// .text:0x800BD300 size:0xA0
void LITXForm(Gap800B993CLight* light, f32 view[3][4]) {
    f32 matrix[3][4];
    CTRLBuildMatrix(&light->control, matrix);
    if (light->parentMatrix != NULL) PSMTXConcat(light->parentMatrix, matrix, matrix);
    PSMTXConcat(view, matrix, matrix);
    PSMTXMultVec(matrix, &light->position, &light->worldPosition);
    PSMTXInverse(matrix, matrix);
    PSMTXTranspose(matrix, matrix);
    PSMTXMultVec(matrix, &light->direction, &light->worldDirection);
}
