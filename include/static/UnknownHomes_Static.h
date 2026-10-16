#ifndef __UNKNOWN_HOMES_STATIC_H_
#define __UNKNOWN_HOMES_STATIC_H_

#include "mssbTypes.h"

extern int fn_8001C67C_animation(int, int);

extern f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax);

typedef struct _GameInitVariables {
    /*0x00*/ int _00;
    /*0x04*/ u16 FrameCountWhileNotAtMainMenu;
    /*0x06*/ u8 _06; // 1 Menu,2 InGame/Minigame/Practice/etc
    /*0x07*/ E(u8, GAME_TYPE) GameModeSelected;
    /*0x08*/ bool exhibitionMatchInd;
    /*0x09*/ E(u8, STADIUM_ID) StadiumID;
    /*0x0A*/ u8 miniGameStadiumIndicator;
    /*0x0B*/ u8 _0B;
    /*0x0C*/ u8 maybeHomeAway;
    /*0x0D*/ u8 maybeHomeAway2;
    /*0x0E*/ u8 home_AwaySetting;
    /*0x0F*/ u8 _0F;
    /*0x10*/ u8 _10;
    /*0x11*/ bool minigamesEnabled;
    /*0x12*/ u8 _12;
    union {
        /*0x13*/ u8 _13;
        /*0x13*/ u8 miniGameLevels[0x20 - 0x13]; // indexed by MINI_GAME_ID
    };
    /*0x20*/ s16 _20[4][2];
    /*0x30*/ s16 challengeMinigame_baseCoinsEarned;
    /*0x32*/ u8 bJMatchRelated;
    /*0x33*/ u8 _33;
    /*0x34*/ u8 humanTeamNumber;
    /*0x35*/ u8 _35;
    /*0x36*/ u8 _36;
    /*0x37*/ u8 challengeDifficulty; // unsure
    /*0x38*/ u8 _38;
    /*0x39*/ u8 bJMatchInd;
    /*0x3A*/ u8 _3A;
    /*0x3B*/ u8 someChallengeModeFlag;
    /*0x3C*/ u8 challengeCaptainStarBought[18];
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
    /*0x50*/ u8 PlayerPorts[2];
    /*0x52*/ u8 _52;
    /*0x53*/ u8 _53;
    /*0x54*/ E(u8, STADIUM_ID) _54;
    /*0x55*/ u8 _55;
    /*0x56*/ u8 _56;
    /*0x57*/ u8 _57;
} GameInitVariables; // size: 0x58

extern GameInitVariables g_d_GameSettings;

typedef struct Camera {
    /* 0x000 */ u8 _pad0[0x4];
    /* 0x004 */ s16 unk4[7];
    /* 0x012 */ u8 unk12;
    /* 0x013 */ u8 _pad13[0x30 - 0x13];
    /* 0x030 */ f32 unk_30;
    /* 0x034 */ f32 unk_34;
    /* 0x038 */ f32 unk_38;
    /* 0x03C */ u8 _pad3C[0xC0 - 0x3C];
    /* 0x0C0 */ f32 unk_C0;
    /* 0x0C4 */ u8 _padC4[0xD0 - 0xC4];
    /* 0x0D0 */ f32 unk_D0;
    /* 0x0D4 */ f32 unk_D4;
    /* 0x0D8 */ f32 unk_D8;
    /* 0x0DC */ f32 unk_DC;
    /* 0x0E0 */ s16 unk_E0;
    /* 0x0E2 */ u8 unk_E2;
    /* 0x0E3 */ u8 unk_E3;
    /* 0x0E4 */ f32 unkE4;
    /* 0x0E8 */ f32 unkE8;
    /* 0x0EC */ f32 unkEC;
    /* 0x0F0 */ f32 unkF0;
    /* 0x0F4 */ f32 unkF4;
    /* 0x0F8 */ f32 unkF8;
    /* 0x0FC */ u8 _padFC[0x108 - 0xFC];
    /* 0x108 */ f32 unk108;
    /* 0x10C */ f32 unk10C;
    /* 0x110 */ f32 unk110;
    /* 0x114 */ f32 unk114;
    /* 0x118 */ s16 unk118;
    /* 0x11A */ s16 unk11A;
    /* 0x11C */ u8 unk11C;
    /* 0x11D */ u8 _pad11D[0xA50 - 0x11D];
    /* 0xA50 */ s32 unk_A50;
    /* 0xA54 */ u8 _pad1[0xA74 - 0xA54];
    /* 0xA74 */ s16 unkA74;
    /* 0xA76 */ s16 unkA76;
    /* 0xA78 */ s16 unkA78;
    /* 0xA7A */ s16 unkA7A;
    /* 0xA7C */ s16 unkA7C;
    /* 0xA7E */ s16 unkA7E;
    /* 0xA80 */ s16 unkA80;
    /* 0xA82 */ s16 unkA82;
    /* 0xA84 */ s16 unkA84[4];    // per-runner, used in fn_3_15144
    /* 0xA8C */ s16 unkA8C[4];    // per-runner, used in fn_3_150C0
    /* 0xA94 */ s16 unkA94;
    /* 0xA96 */ s16 unkA96;       // used in fn_3_14FC8
    /* 0xA98 */ s16 unkA98;       // Offset 0xA98
    /* 0xA9A */ s16 unkA9A;
    /* 0xA9C */ s16 unkA9C;       // Offset 0xA9C: used in fn_3_14F24
    /* 0xA9E */ s16 unkA9E;
    /* 0xAA0 */ s16 unkAA0;
    /* 0xAA2 */ s16 unkAA2;
    /* 0xAA4 */ s16 unkAA4;       // used in fn_3_14E84
    /* 0xAA6 */ s16 unkAA6;       // used in fn_3_14EE8
    /* 0xAA8 */ u8 _pad4[0xAB4 - 0xAA8];
    /* 0xAB4 */ u8 unkAB4;
    /* 0xAB5 */ u8 unkAB5;
    /* 0xAB6 */ u8 unkAB6;
    /* 0xAB7 */ u8 unkAB7;
    /* 0xAB8 */ u8 unkAB8;
    /* 0xAB9 */ u8 unkAB9;
    /* 0xABA */ u8 unkABA;
    /* 0xABB */ u8 unkABB[4];     // per-runner, used in fn_3_15144
    /* 0xABF */ u8 unkABF;
    /* 0xAC0 */ u8 unkAC0[4];    // per-runner
    /* 0xAC4 */ u8 unkAC4;
    /* 0xAC5 */ u8 cameraFlag;
    /* 0xAC6 */ u8 unkAC6;
    /* 0xAC7 */ u8 _pad5[0xAC8 - 0xAC7];
    /* 0xAC8 */ u8 unkAC8;
    /* 0xAC9 */ u8 _pad5b[0xACA - 0xAC9];
    /* 0xACA */ u8 unkACA;
    /* 0xACB */ u8 _pad5c[0xAD8 - 0xACB];
    /* 0xAD8 */ u8 cameraFlag2;
    /* 0xAD9 */ u8 _pad6[0x2828 - 0xAD9];
    /* 0x2828 */ f32 unk2828;
    /* 0x282C */ f32 unk282C;
    /* 0x2830 */ f32 unk2830;
    /* 0x2834 */ u8 _pad6a[0x2838 - 0x2834];
    /* 0x2838 */ s16 unk2838;
    /* 0x283A */ u8 _pad6b[0x283C - 0x283A];
    /* 0x283C */ s16 unk283C;
    /* 0x283E */ u8 unk283E;
    /* 0x283F */ u8 unk283F;
    /* 0x2840 */ f32 unk2840;
    /* 0x2844 */ f32 unk2844;
    /* 0x2848 */ f32 unk2848;
    /* 0x284C */ f32 unk284C;
    /* 0x2850 */ f32 unk2850;
    /* 0x2854 */ f32 unk2854;
    /* 0x2858 */ f32 unk2858;
    /* 0x285C */ f32 unk285C;
    /* 0x2860 */ f32 unk2860;
    /* 0x2864 */ u8 _pad7[0x2870 - 0x2864];
    /* 0x2870 */ f32 unk2870;
    /* 0x2874 */ f32 unk2874;
    /* 0x2878 */ f32 unk2878;
    /* 0x287C */ f32 unk287C;
    /* 0x2880 */ f32 unk2880;
    /* 0x2884 */ u8 _pad2884[0x28A7 - 0x2884];
    /* 0x28A7 */ u8 unk28A7;
    /* 0x28A8 */ u8 unk28A8;
} Camera;

typedef struct Strikes {
    /* 0x00 */ s32 strikes;      // Target for lwz r4, 0x0(r5)
    /* 0x04 */ s32 balls;        // Target for lwz r3, 0x4(r5)
    /* 0x08 */ s32 outs;
    s32 unk_C;           /* 0x0C */
    s32 unk_10;          /* 0x10 */
    s32 unk_14;          /* 0x14 */
    s16 unk_18[3];       /* 0x18 - Array of strike values */
    s16 unk_1E;          /* 0x1E */
    u8 unk_20;           /* 0x20 */
    u8 unk_21;           /* 0x21 */
} Strikes; // Total size likely 0x1E or padded to 0x20

extern Camera* g_pCamera;
extern Strikes g_Strikes;


#endif // !__UNKNOWN_HOMES_STATIC_H_
