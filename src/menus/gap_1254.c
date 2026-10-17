#include "menus/gap_1254.h"
#include "menus/rep_0438.h"
#include "game/rep_3448.h"
#include "menus/gap_D08.h"
#include "menus/gap_71EC4.h"
#include "string.h"
#include "menus/rep_0568.h"
#include "menus/gap_16870.h"

extern void fn_800AD038(u32 value);

extern u8 lbl_2_bss_100B4;

extern u32 lbl_803CB750;
extern void fn_800625A4(s32 index, s32 command);

// .text:0x00001254 size:0x4
void fn_2_1254(void) {
    return;
}

// .text:0x00001258 size:0x48
void fn_2_1258(void) {
    return;
}

// .text:0x000012A0 size:0x2C
void fn_2_12A0(s16* value, s16 amount) {
    if (*value < 0x7FFF - amount) *value += amount;
    else *value = 0x7FFF;
}

// .text:0x000012CC size:0x2C
void fn_2_12CC(u8* value, u16 amount) {
    if (*value + amount > 0xFF) *value = 0xFF;
    else *value += amount;
}

// .text:0x000012F8 size:0x30
void fn_2_12F8(u16* value, u16 amount) {
    if (*value + amount > 0xFFFF) *value = 0xFFFF;
    else *value += amount;
}

// .text:0x00001328 size:0x2C
void fn_2_1328(u32* value, u16 amount) {
    u32 result = *value + amount;
    if (result > 0x7FFFFFFF) *value = 0x7FFFFFFF;
    else *value = result;
}

// .text:0x00001354 size:0x108
void fn_2_1354(void) {
    return;
}

// .text:0x0000145C size:0x30
void fn_2_145C(void) {
    return;
}

// .text:0x0000148C size:0x6C
s32 fn_2_148C(u16* text) {
    s32 width = 0;
    for (;;) {
        u16 code = *text++;
        if (code & 0x4000) {
            switch (code & 0x3FFF) {
            case 0: goto done;
            case 2: width += 11; break;
            case 3: width += 22; break;
            }
        } else if (code & 0x8000) {
            width += 22;
        } else {
            width += 11;
        }
    }
done:
    return width;
}

// .text:0x000014F8 size:0x5C
void fn_2_14F8(void) {
    return;
}

// .text:0x00001554 size:0x24
u32 fn_2_1554(void) {
    return lbl_803CB750 = lbl_803CB750 * 0x5D588B65 + 1;
}

// .text:0x00001578 size:0x288
void fn_2_1578(void) {
    return;
}

// .text:0x00001800 size:0x288
void fn_2_1800(void) {
    return;
}

// .text:0x00001A88 size:0x124
void fn_2_1A88(void) {
    return;
}

// .text:0x00001BAC size:0x88
void fn_2_1BAC(void) {
    memset(lbl_803C66B0.resetData, 0, sizeof(lbl_803C66B0.resetData));
    lbl_803C66B0.unk56 = 0;
    lbl_803C66B0.unk55 = 0;
    memset(&lbl_803C5EA4, 0, sizeof(MenusSceneFlags));
    memset(lbl_8034E9A0.resetData, 0, sizeof(lbl_8034E9A0.resetData));
    memset(&lbl_8034E978, 0, sizeof(MenusSceneTransition));
}

// .text:0x00001C34 size:0xF4
void fn_2_1C34(void) {
    return;
}

// .text:0x00001D28 size:0x2C
void fn_2_1D28(void) {
    lbl_8034E9A0.unk472A = 0xFF;
    lbl_8034E9A0.unk4756 = 0;
    lbl_8034E9A0.unk4754 = 0;
    lbl_8034E9A0.unk4755 = 3;
    lbl_8034E9A0.unk48B3 = 0;
}

// .text:0x00001D54 size:0x70
void fn_2_1D54(s32* value, u8 index, s32 count) {
    u16 buttons = lbl_8034E9A0.input[index].buttons;
    if (buttons & 8) {
        --*value;
        if (*value < 0) *value = count - 1;
    } else if (buttons & 4) {
        ++*value;
        if (*value == count) *value = 0;
    }
}

// .text:0x00001DC4 size:0x4
void fn_2_1DC4(void) {
    return;
}

// .text:0x00001DC8 size:0x168
void fn_2_1DC8(void) {
    return;
}

// .text:0x00001F30 size:0x8B0
void fn_2_1F30(void) {
    return;
}

// .text:0x000027E0 size:0x3D8
void fn_2_27E0(void) {
    return;
}

// .text:0x00002BB8 size:0x164
void fn_2_2BB8(void) {
    return;
}

// .text:0x00002D1C size:0x2A4
void fn_2_2D1C(void) {
    return;
}

// .text:0x00002FC0 size:0x244
void fn_2_2FC0(u8 mode, s32 update, s32 reset) {
    return;
}

// .text:0x00003204 size:0x38
void fn_2_3204(void) {
    fn_2_2FC0(lbl_803297E0.mode, 1, 1);
}

// .text:0x0000323C size:0x180
void fn_2_323C(void) {
    return;
}

// .text:0x000033BC size:0xD0
void fn_2_33BC(void) {
    return;
}

// .text:0x0000348C size:0x144
void fn_2_348C(void) {
    return;
}

// .text:0x000035D0 size:0x54
void fn_2_35D0(void) {
    return;
}

// .text:0x00003624 size:0x134C
void fn_2_3624(void) {
    return;
}

// .text:0x00004970 size:0x814
void fn_2_4970(void) {
    return;
}

// .text:0x00005184 size:0x148
void fn_2_5184(void) {
    return;
}

// .text:0x000052CC size:0x178
void fn_2_52CC(void) {
    return;
}

// .text:0x00005444 size:0x3A4
void fn_2_5444(void) {
    return;
}

// .text:0x000057E8 size:0x8
s32 fn_2_57E8(s32 arg0, s32 arg1) {
    return (s8)arg1;
}

// .text:0x000057F0 size:0x790
void fn_2_57F0(void) {
    return;
}

// .text:0x00005F80 size:0x118
void fn_2_5F80(void) {
    return;
}

// .text:0x00006098 size:0x3C
void fn_2_6098(u8 index) {
    lbl_2_bss_F468.states[index] = 9;
    fn_800625A4(index, 0x17);
}

// .text:0x000060D4 size:0x64
s32 fn_2_60D4(u8 index) {
    if (g_d_GameSettings.GameModeSelected != 5) return lbl_8034E9A0.players[index];
    if (index != 0) return lbl_8034E9A0.players[index];
    return lbl_8034E9A0.players[index];
}

// .text:0x00006138 size:0x68
void fn_2_6138(void) {
    fn_800625A4(0, 0x13);
    fn_800625A4(1, 0x13);
    lbl_2_bss_F468.unk4F = 0;
    lbl_2_bss_F468.unk2E = 0;
    lbl_2_bss_100B4 = 1;
    lbl_803CBBCC->state = 8;
}

// .text:0x000061A0 size:0x2E4
void fn_2_61A0(void) {
    return;
}

// .text:0x00006484 size:0x184
void fn_2_6484(void) {
    return;
}

// .text:0x00006608 size:0x17C
void fn_2_6608(void) {
    return;
}

// .text:0x00006784 size:0x100
void fn_2_6784(void) {
    return;
}

// .text:0x00006884 size:0x270
void fn_2_6884(void) {
    return;
}

// .text:0x00006AF4 size:0x248
void fn_2_6AF4(void) {
    return;
}

// .text:0x00006D3C size:0x7C8
void fn_2_6D3C(void) {
    return;
}

// .text:0x00007504 size:0x840
void fn_2_7504(void) {
    return;
}

// .text:0x00007D44 size:0x98
void fn_2_7D44(void) {
    if (lbl_803CBBCC->previousSelection == 9) {
        memset(&lbl_2_bss_100B8, 0, sizeof(Rep0568State));
    }
    lbl_8034E9A0.unk4755 = 1;
    lbl_2_bss_100B8.count = 4;
    fn_2_16A74(0, 0);
    fn_2_16A74(1, 0);
    fn_2_16A74(2, 0);
    fn_2_16A74(3, 0);
}

// .text:0x00007DDC size:0x910
void fn_2_7DDC(void) {
    return;
}

// .text:0x000086EC size:0x94
void fn_2_86EC(void) {
    return;
}

// .text:0x00008780 size:0x14
s32 fn_2_8780(s32 mode) {
    s32 result = 9;
    if (mode != 0) result = 19;
    return result;
}

// .text:0x00008794 size:0x14
s32 fn_2_8794(s32 mode, s32 index) {
    if (mode != 0) index += 10;
    return index;
}

// .text:0x000087A8 size:0x194
void fn_2_87A8(void) {
    return;
}

// .text:0x0000893C size:0x4
void fn_2_893C(void) {
    return;
}

// .text:0x00008940 size:0x3B8
void fn_2_8940(void) {
    return;
}

// .text:0x00008CF8 size:0x8E0
void fn_2_8CF8(void) {
    return;
}

// .text:0x000095D8 size:0x4F4
void fn_2_95D8(void) {
    return;
}

// .text:0x00009ACC size:0x4A4
void fn_2_9ACC(void) {
    return;
}

// .text:0x00009F70 size:0xD0
void fn_2_9F70(void) {
    return;
}

// .text:0x0000A040 size:0x160
void fn_2_A040(void) {
    return;
}

// .text:0x0000A1A0 size:0xE8
void fn_2_A1A0(void) {
    return;
}

// .text:0x0000A288 size:0x284
void fn_2_A288(void) {
    return;
}

// .text:0x0000A50C size:0x120
void fn_2_A50C(void) {
    return;
}

// .text:0x0000A62C size:0xB4
BOOL fn_2_A62C(void) {
    s32 i, j;
    for (i = 0; i < 9; i++) {
        s32 value = lbl_803C6724.first[i];
        for (j = 0; j < 9; j++) {
            if (value == lbl_803C6724.second[j] && value != 255) return 1;
        }
    }
    return 0;
}

// .text:0x0000A6E0 size:0x4E0
void fn_2_A6E0(void) {
    return;
}

// .text:0x0000ABC0 size:0x328
void fn_2_ABC0(void) {
    return;
}

// .text:0x0000AEE8 size:0x43C
void fn_2_AEE8(void) {
    return;
}

// .text:0x0000B324 size:0x1E4
void fn_2_B324(void) {
    return;
}

// .text:0x0000B508 size:0x164
void fn_2_B508(void) {
    return;
}

// .text:0x0000B66C size:0x2B4
void fn_2_B66C(void) {
    return;
}

// .text:0x0000B920 size:0x670
void fn_2_B920(void) {
    return;
}

// .text:0x0000BF90 size:0x394
void fn_2_BF90(void) {
    return;
}

// .text:0x0000C324 size:0x160
void fn_2_C324(void) {
    return;
}

// .text:0x0000C484 size:0x214
void fn_2_C484(void) {
    return;
}

// .text:0x0000C698 size:0x144
void fn_2_C698(void) {
    return;
}

// .text:0x0000C7DC size:0x284
void fn_2_C7DC(void) {
    return;
}

// .text:0x0000CA60 size:0x25C
void fn_2_CA60(void) {
    return;
}

// .text:0x0000CCBC size:0x24
void fn_2_CCBC(void) {
    fn_2_7DDC();
    fn_2_7504();
}

// .text:0x0000CCE0 size:0x164
void fn_2_CCE0(void) {
    return;
}

// .text:0x0000CE44 size:0x1168
void fn_2_CE44(void) {
    return;
}

// .text:0x0000DFAC size:0xB34
void fn_2_DFAC(void) {
    return;
}

// .text:0x0000EAE0 size:0x154
void fn_2_EAE0(void) {
    return;
}

// .text:0x0000EC34 size:0x20
void fn_2_EC34(void) {
    if (lbl_2_bss_F468.unk56 == 0) lbl_2_bss_F468.unk56 = 1;
}

// .text:0x0000EC54 size:0x140
void fn_2_EC54(void) {
    return;
}

// .text:0x0000ED94 size:0x46C
void fn_2_ED94(void) {
    return;
}

// .text:0x0000F200 size:0x8A0
void fn_2_F200(void) {
    return;
}

// .text:0x0000FAA0 size:0x214
void fn_2_FAA0(void) {
    return;
}

// .text:0x0000FCB4 size:0x614
void fn_2_FCB4(void) {
    return;
}

// .text:0x000102C8 size:0x234
void fn_2_102C8(void) {
    return;
}

// .text:0x000104FC size:0xBB4
void fn_2_104FC(void) {
    return;
}

// .text:0x000110B0 size:0x244
void fn_2_110B0(void) {
    return;
}

// .text:0x000112F4 size:0x4C
BOOL fn_2_112F4(DrawingSceneStruct* scene, s32 offset, s32 index, u16* ids, u16 value) {
    Struct_80371C30_Inner* obj = lbl_80371C30[scene->unkIndex + offset].obj;
    if ((s32)(obj->field_0x5C >> 16) == ids[index + 1] - 1) {
        obj->unk64 = value;
        return TRUE;
    }
    return FALSE;
}

// .text:0x00011340 size:0x358
void fn_2_11340(void) {
    return;
}

// .text:0x00011698 size:0x810
void fn_2_11698(void) {
    return;
}

// .text:0x00011EA8 size:0x228
void fn_2_11EA8(void) {
    return;
}

// .text:0x000120D0 size:0x9C
void fn_2_120D0(void) {
    lbl_8034E9A0.unk48AD = 1;
    lbl_8034E9A0.unk4755 = 3;
    lbl_803C66B0.unk0 = 0;
    lbl_803C66B0.unk5A = 0;
    lbl_803C66B0.unk59 = 0;
    lbl_8034E9A0.unk472A = 0xFF;
    lbl_8034E9A0.unk48AF = 1;
    lbl_8034E9A0.unk48B1 = 1;
    memset(lbl_803C66B0.resetData, 0, 6);
    lbl_8034E978.unk26 = 1;
    fn_800AD038(lbl_8034E9A0.timeHigh);
    g_d_GameSettings._10 = 0;
}

// .text:0x0001216C size:0xCC
void fn_2_1216C(void) {
    return;
}
