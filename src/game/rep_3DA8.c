#include "game/rep_3DA8.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/gap_1658F0.h"

// .text:0x0016230C size:0xA48 mapped:0x807A13A0
void fn_3_16230C(void) {
    return;
}


// .text:0x001637EC size:0x15C mapped:0x807A2880
void fn_3_1637EC(void) {
    s16 ids[9];
    ChallengeSaveData* tracker;
    u8 difficulty;
    u8 captain;
    s32 i;
    s8 flags;
    s32 j;
    ChallengeTrackingStruct* m;
    tracker = &starMissionCompletionTracker;
    captain = tracker->challengeCaptain;
    difficulty = tracker->challengeDifficulty;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    for (j = 0; j < 9; j++) {
        if (ids[j] != -1) {
            m = &tracker->missions[ids[j]];
            flags = m->scoutFlagPointer->flags[difficulty][captain];
            if (flags != 0 && (s8)m->scoutFlagsAchieved < flags) {
                m->scoutFlagsAchieved = flags;
            }
        }
    }
}

// .text:0x00163948 size:0x134 mapped:0x807A29DC
BOOL fn_3_163948(void) {
    s16 ids[9];
    ScoutFlagPair* pairs;
    s32 i;
    BOOL ret;
    s32 j;
    pairs = lbl_3_common_bss_37400.scoutFlags;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    ret = FALSE;
    for (j = 0; j < 9; j++) {
        if (ids[j] != -1) {
            if (pairs[j].newFlags != 0 && pairs[j].oldFlags < pairs[j].newFlags) {
                ret = TRUE;
            }
        }
    }
    return ret;
}

// .text:0x00163A7C size:0x158 mapped:0x807A2B10
BOOL fn_3_163A7C(void) {
    s16 ids[9];
    ChallengeSaveData* tracker;
    Bss37400Item* bss;
    InMemBatterType* batter;
    InMemPitcherType* pitcher;
    u8 captain;
    u8 difficulty;
    s32 i;
    s32 charID;
    BOOL ret;
    s32 j;
    tracker = &starMissionCompletionTracker;
    bss = &lbl_3_common_bss_37400;
    batter = &g_Batter;
    pitcher = &g_Pitcher;
    captain = tracker->challengeCaptain;
    difficulty = tracker->challengeDifficulty;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    if (bss->unk46 == 2) {
        charID = pitcher->charID;
    } else if (bss->unk46 == 1) {
        charID = batter->charID;
    }
    for (j = 0; j < 9; j++) {
        if (charID == ids[j]) {
            if (tracker->missions[ids[j]].scoutFlagPointer->flags[difficulty][captain] != 0) {
                ret = TRUE;
            }
        }
    }
    return ret;
}

// .text:0x00163BD4 size:0x160 mapped:0x807A2C68
BOOL fn_3_163BD4(void) {
    s16 ids[9];
    ChallengeSaveData* tracker;
    u8 captain;
    u8 difficulty;
    s32 i;
    s8 flags;
    BOOL ret;
    s32 j;
    ChallengeTrackingStruct* m;
    tracker = &starMissionCompletionTracker;
    captain = tracker->challengeCaptain;
    difficulty = tracker->challengeDifficulty;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    ret = FALSE;
    for (j = 0; j < 9; j++) {
        if (ids[j] != -1) {
            m = &tracker->missions[ids[j]];
            flags = m->scoutFlagPointer->flags[difficulty][captain];
            if (flags != 0 && (s8)m->scoutFlagsAchieved < flags) {
                ret = TRUE;
            }
        }
    }
    return ret;
}

// .text:0x00163D34 size:0x160 mapped:0x807A2DC8
void fn_3_163D34(void) {
    s16 ids[9];
    ChallengeSaveData* tracker;
    ScoutFlagPair* pairs;
    u8 captain;
    u8 difficulty;
    s32 i;
    s32 j;
    ChallengeTrackingStruct* m;
    tracker = &starMissionCompletionTracker;
    pairs = lbl_3_common_bss_37400.scoutFlags;
    captain = tracker->challengeCaptain;
    difficulty = tracker->challengeDifficulty;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    for (j = 0; j < 9; j++) {
        if (ids[j] != -1) {
            m = &tracker->missions[ids[j]];
            if (m->scoutFlagPointer->flags[difficulty][captain] != 0) {
                pairs[j].oldFlags = m->scoutFlagsAchieved;
                pairs[j].newFlags = m->scoutFlagPointer->flags[difficulty][captain];
            }
        }
    }
}
