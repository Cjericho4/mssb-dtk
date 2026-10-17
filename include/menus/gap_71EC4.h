#ifndef __MENUS_gap_71EC4_H_
#define __MENUS_gap_71EC4_H_

#include "mssbTypes.h"
#include "menus/rep_0B08.h"

typedef struct MenusInputFlags {
    u8 unk0;
    union {
        struct {
            u8 _pad1[6];
            u8 state;
            u8 _pad8[5];
            u8 flags[4];
            u8 _pad11[0x3E];
            u8 state4F;
            u8 _pad50[5];
        };
        u8 resetData[0x54];
    };
    u8 unk55;
    u8 unk56;
    u8 _pad57[2];
    u8 unk59;
    u8 unk5A;
} MenusInputFlags;
extern MenusInputFlags lbl_803C66B0;

typedef struct MenusSceneScript MenusSceneScript;
struct DrawingSceneStruct;
void fn_80034E20(struct DrawingSceneStruct* scene, MenusSceneScript* script);
typedef struct MenusSceneFlags {
    u8 _pad0[5];
    u8 unk5;
    u8 _pad6[0x31];
    u8 unk37;
    u8 unk38;
    u8 _pad39;
} MenusSceneFlags;
extern MenusSceneFlags lbl_803C5EA4;

typedef struct MenusQueueState {
    u8 _pad0[0x47];
    u8 pending;
} MenusQueueState;
extern MenusQueueState lbl_803C50E8;

typedef struct MenusSceneTransition {
    u8 state;
    u8 _pad1[7];
    u8 current;
    u8 previous;
    u8 _padA[0x1C];
    u8 unk26;
    u8 _pad27;
} MenusSceneTransition;

typedef struct MenusTransitionConfig {
    u8 _pad0[0x58];
    u16 next;
    u8 _pad5A[0x6E];
    u16 nextC8;
    u8 _padCA[0x4EE];
    u16 next5B8;
} MenusTransitionConfig;
extern MenusSceneTransition lbl_8034E978;
extern MenusTransitionConfig lbl_800FEF70;

void fn_2_71EC4(Rep0B08Obj* obj);
void fn_2_71EFC(Rep0B08Obj* obj);
void fn_2_71F20(Rep0B08Obj* obj);
void fn_2_71F60(void);
void fn_2_72038(s32 index, s16 value);
void fn_2_72054(s32 index, u8 variant);
void fn_2_7207C(void);
void fn_2_72594(void);
void fn_2_72630(void);
void fn_2_7265C(void);
void fn_2_72814(void);
void fn_2_728C0(void);
void fn_2_7293C(void);
void fn_2_729E0(void);
void fn_2_72A58(void);
void fn_2_72A88(void);
void fn_2_72CB4(void);
void fn_2_72D60(void);
void fn_2_72DDC(void);
void fn_2_72E54(void);
void fn_2_73028(void);
void fn_2_7302C(void);
void fn_2_7308C(void);
void fn_2_73758(void);
void fn_2_738C8(void);
void fn_2_73994(void);
s32 fn_2_73B54(s32 value);
s32 fn_2_73B94(s32 value);
void fn_2_73BF0(void);
void fn_2_73CBC(void);
void fn_2_73EFC(void);
void fn_2_744C8(void);
void fn_2_74518(void);
void fn_2_74564(void);
void fn_2_7463C(void);
void fn_2_747FC(void);
void fn_2_74CD8(void);
void fn_2_74D8C(void);
s32 fn_2_74DB8(s32 value);
void fn_2_74E14(void);
void fn_2_74F40(void);
void fn_2_75B58(void);
void fn_2_75BE4(void);
void fn_2_76098(void);
void fn_2_7609C(s32 unused, u8 mode, u8 flag);
void fn_2_760CC(void);
void fn_2_7630C(void);
void fn_2_7664C(void);
void fn_2_76650(void);
void fn_2_76874(void);
void fn_2_76DF0(void);
void fn_2_776A0(void);
void fn_2_78034(s32 unused, s32 index);
void fn_2_7805C(void);
void fn_2_7836C(void);
void fn_2_78AC0(void);
void fn_2_78F78(void);
void fn_2_7912C(void);
void fn_2_79394(void);
void fn_2_79634(void);
void fn_2_79688(void);
void fn_2_79764(void);
void fn_2_79930(void);
void fn_2_79B24(void);
void fn_2_79CF8(void);
void fn_2_79FAC(void);
void fn_2_7A194(void);
void fn_2_7A460(void);
void fn_2_7A5B8(void);
void fn_2_7A748(void);
void fn_2_7A9D8(void);
void fn_2_7AC64(void);
void fn_2_7AE3C(void);
void fn_2_7BFF8(void);
void fn_2_7D85C(void);
void fn_2_7DAB8(void);
void fn_2_7E194(void);
void fn_2_7E380(void);
void fn_2_7E860(void);
void fn_2_7E974(void);
void fn_2_7EE7C(void);
void fn_2_7EF68(void);
void fn_2_7F030(void);
void fn_2_7F2BC(void);
void fn_2_7F714(void);
void fn_2_7F8BC(void);
void fn_2_7FAFC(void);
void fn_2_800B0(void);
void fn_2_802EC(void);
void fn_2_80500(void);
void fn_2_805DC(void);
void fn_2_8082C(void);
void fn_2_808D8(void);
void fn_2_80B5C(void);
void fn_2_80C2C(void);
void fn_2_80E0C(void);
void fn_2_80F5C(void);
void fn_2_81628(void);
void fn_2_8279C(void);
void fn_2_82CF0(void);
void fn_2_82DE8(void);
void fn_2_82E58(void);
void fn_2_82EC0(void);
void fn_2_834F0(void);
void fn_2_836A4(void);
void fn_2_83744(void);
void fn_2_837D8(void);
void fn_2_83974(void);
void fn_2_83B34(void);
void fn_2_84194(void);
void fn_2_84388(void);
void fn_2_845A8(void);
void fn_2_84FA8(void);
void fn_2_85108(void);
void fn_2_8515C(void);
void fn_2_85160(void);
void fn_2_851A8(void);
void fn_2_85310(void);
void fn_2_854B0(void);

#endif // !__MENUS_gap_71EC4_H_
