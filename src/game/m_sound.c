#include "game/m_sound.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "musyx/musyx.h"
#include "musyx/seq.h"
#include "game/rep_720.h"

/* Per-sound-effect mix settings, indexed by (soundID - SFX_SETTINGS_BASE). */
#define SFX_SETTINGS_BASE 0x151
typedef struct {
    u8 volume;
    u8 pan;
} SoundFXSettings;

typedef struct {
    u16 seqID;
    u16 groupID;
    u16 _4;
} SongEntry; /* size: 0x6 */

typedef struct {
    u8 volume;
    u8 _1;
} SongSettings;

/* Sound tables starting at .data 0x8148. */
typedef struct {
    u8 _pad0[0x1C4];
    SongSettings songSettings[0x10];  /* 0x1C4 */
    u8 _pad1E4[0x798 - 0x1E4];
    SongEntry songs[19];              /* 0x798 */
    u8 _pad80A[0x2];
    SongEntry practiceSongs[1];       /* 0x80C */
} SoundTables;

extern SoundTables lbl_3_data_8148;
extern SongSettings lbl_3_data_830C[]; /* == lbl_3_data_8148.songSettings */
extern SongEntry lbl_3_data_88E0[];    /* == lbl_3_data_8148.songs */
extern u16 lbl_3_data_8168[];
extern SoundFXSettings lbl_3_data_8338[];
/* Per-voice mix settings for grouped sound effects. */
typedef struct {
    u8 volume[0x180];
    u8 pan[0x180];
    u8 _pad300[0x7C];
} VoiceMixTable; /* size: 0x37C */
extern VoiceMixTable lbl_3_data_8530;
/* Loaded song arrangement (.arr) data, indexed by song. */
struct SongArrangement;
extern struct SongArrangement** lbl_3_bss_1774;

extern void fn_3_8B094(void);
extern u32 sndSeqGetValid(u32);
extern void sndSeqVolume(u8 volume, u16 time, u32 seqId, u8 mode);

/* Sound command ring buffer stored in the sound queue entry. */
typedef struct {
    u8 cmd;  /* 0x0 */
    u8 arg1; /* 0x1 */
    u8 arg2; /* 0x2 */
} SoundCommand;

typedef struct {
    u8 _pad0[0x14];
    u8 writeIdx;               /* 0x14 */
    u8 readIdx;                /* 0x15 */
    SoundCommand commands[14]; /* 0x16 */
} SoundQueue;

static SoundQueue* lbl_3_bss_1768;

// .text:0x0008B258 size:0x8C mapped:0x806CA2EC
BOOL fn_3_8B258(u8 arg1, u8 cmd, u8 arg2) {
    u8 idx;
    u8 next;

    if (lbl_3_bss_1768 == NULL || lbl_3_bss_1768->readIdx == (next = ((idx = lbl_3_bss_1768->writeIdx) + 1) % 14)) {
        return FALSE;
    }
    lbl_3_bss_1768->writeIdx = next;
    lbl_3_bss_1768->commands[idx].cmd = cmd;
    lbl_3_bss_1768->commands[idx].arg1 = arg1;
    lbl_3_bss_1768->commands[idx].arg2 = arg2;
    return TRUE;
}

// .text:0x0008B2E4 size:0x34 mapped:0x806CA378
void fn_3_8B2E4(void) {
    lbl_3_bss_1768 = (SoundQueue*)fn_800B0A5C_insertQueue(fn_3_8B094, 0);
}

// .text:0x0008B318 size:0x400 mapped:0x806CA3AC
void fn_3_8B318(s32 arg0) {
    return;
}

// .text:0x0008B718 size:0xC4 mapped:0x806CA7AC
void fn_3_8B718(void) {
    return;
}

// .text:0x0008B7DC size:0x28 mapped:0x806CA870
void fn_3_8B7DC(void) {
    sndRemoveListener(&lbl_3_common_bss_32B20);
}

// .text:0x0008B804 size:0x8C mapped:0x806CA898
void fn_3_8B804(void) {
    return;
}

// .text:0x0008B890 size:0xD4 mapped:0x806CA924
void fn_3_8B890(void) {
    return;
}

// .text:0x0008B964 size:0x58 mapped:0x806CA9F8
void fn_3_8B964(VecXYZ* pos, VecXYZ* vel, VecXYZ* orient) {
    if (lbl_3_common_bss_32B20.field_0x8 != 0) {
        sndUpdateListener(&lbl_3_common_bss_32B20, pos, vel, orient, &lbl_3_data_8D70, 0x7F, 0);
    }
}

// .text:0x0008B9BC size:0xA4 mapped:0x806CAA50
void fn_3_8B9BC(void) {
    return;
}

// .text:0x0008BA60 size:0x164 mapped:0x806CAAF4
void fn_3_8BA60(void) {
    return;
}

// .text:0x0008BBC4 size:0x230 mapped:0x806CAC58
void fn_3_8BBC4(s32 soundID, VecXYZ* pos, s32 arg2, s32 arg3) {
    return;
}

// .text:0x0008BDF4 size:0x98 mapped:0x806CAE88
void fn_3_8BDF4(void) {
    return;
}

// .text:0x0008BE8C size:0x1F0 mapped:0x806CAF20
void fn_3_8BE8C(void) {
    return;
}

// .text:0x0008C07C size:0x88 mapped:0x806CB110
void fn_3_8C07C(void) {
    u8 idx;
    u8 next;

    if (lbl_3_bss_1768 == NULL) {
        return;
    }
    idx = lbl_3_bss_1768->writeIdx;
    if (lbl_3_bss_1768->readIdx == (next = (idx + 1) % 14)) {
        return;
    }
    lbl_3_bss_1768->writeIdx = next;
    lbl_3_bss_1768->commands[idx].cmd = 0;
    lbl_3_bss_1768->commands[idx].arg1 = 4;
    lbl_3_bss_1768->commands[idx].arg2 = 0;
}

// .text:0x0008C104 size:0x1D8 mapped:0x806CB198
void fn_3_8C104(void) {
    return;
}

// .text:0x0008C2DC size:0x214 mapped:0x806CB370
void fn_3_8C2DC(void) {
    return;
}

// .text:0x0008C4F0 size:0xD8 mapped:0x806CB584
void fn_3_8C4F0(void) {
    return;
}

// .text:0x0008C5C8 size:0x7AC mapped:0x806CB65C
void fn_3_8C5C8(void) {
    return;
}

// .text:0x0008CD74 size:0xC4C mapped:0x806CBE08
void fn_3_8CD74(void) {
    return;
}

// .text:0x0008D9C0 size:0xC0 mapped:0x806CCA54
void fn_3_8D9C0(void) {
    return;
}

// .text:0x0008DA80 size:0x1748 mapped:0x806CCB14
void fn_3_8DA80(void) {
    return;
}

// .text:0x0008F1C8 size:0x54 mapped:0x806CE25C
void fn_3_8F1C8(void) {
    lbl_3_common_bss_34C58._20 = -1;
    lbl_3_common_bss_34C58._22 = -1;
    lbl_3_common_bss_34C58._29 = 0;
    lbl_3_common_bss_34C58._2A = 0;
    lbl_3_bss_1768 = (SoundQueue*)fn_800B0A5C_insertQueue(fn_3_8B094, 0);
}

// .text:0x0008F21C size:0x9F0 mapped:0x806CE2B0
void fn_3_8F21C(void) {
    return;
}

// .text:0x0008FC0C size:0x74 mapped:0x806CECA0
void fn_3_8FC0C(void) {
    Struct34C58* ptr = &lbl_3_common_bss_34C58;

    ptr->_26 = 0;
    if (ptr->_10 != (u32)-1) {
        sndFXKeyOff(ptr->_10);
        ptr->_10 = -1;
    }

    ptr = &lbl_3_common_bss_34C58;
    if (ptr->_14 != (u32)-1) {
        sndFXKeyOff(ptr->_14);
        ptr->_14 = -1;
    }
}

// .text:0x0008FC80 size:0x298 mapped:0x806CED14
void fn_3_8FC80(void) {
    return;
}

// .text:0x0008FF18 size:0x44 mapped:0x806CEFAC



void fn_3_8FF18(void) {
    Struct34C58* ptr;
    ptr =   &lbl_3_common_bss_34C58;

    //Not sure why this order, but its needed to match
    ptr->_0C = -1;
    lbl_3_bss_1780 = -1;

    ptr->_10 = -1;
    ptr->_14 = -1;
    ptr->_18 = -1;
    ptr->_1C = -1;
    ptr->_28 = 0;
    ptr->_04 = -1;
    ptr->_08 = -1;
    ptr->_2F = 0;
    ptr->_33 = 0;
}

// .text:0x0008FF5C size:0x108 mapped:0x806CEFF0
u32 fn_3_8FF5C(s32 soundID, f32 x, f32 z) {
    s32 screenX;
    s32 screenY;
    s32 pan;
    SND_VOICEID vid;

    pan = 0x3F;
    if (lbl_800EF808.soundMode == 1) {
        fn_3_1650C(&screenX, &screenY, 1, x, -z);
        if (screenX < 0) {
            pan = 0;
        } else if (screenX > 640) {
            pan = 0x7F;
        } else {
            pan = 127.0f * (screenX / 640.0f);
        }
    }
    vid = sndFXStartEx(soundID, lbl_3_data_8338[soundID - SFX_SETTINGS_BASE].volume, pan, 0);
    sndFXCtrl(vid, 0x5B, lbl_3_data_8338[soundID - SFX_SETTINGS_BASE].pan);
    return vid;
}

// .text:0x00090064 size:0xEC mapped:0x806CF0F8
void fn_3_90064(void) {
    return;
}

// .text:0x00090150 size:0xD0 mapped:0x806CF1E4
void fn_3_90150(void) {
    return;
}

// .text:0x00090220 size:0x74 mapped:0x806CF2B4
u32 fn_3_90220(s32 arg0, s32 arg1) {
    u8 pan = lbl_3_data_8530.pan[arg1];
    SND_VOICEID vid = sndFXStartEx(arg1 + lbl_3_data_8168[arg0], lbl_3_data_8530.volume[arg1], 0x3F, 0);

    sndFXCtrl(vid, 0x5B, pan);
    return vid;
}

// .text:0x00090294 size:0x64 mapped:0x806CF328
SND_VOICEID playSoundEffect(int arg0) {
    SND_VOICEID vid = sndFXStartEx((u16)arg0, lbl_3_data_8338[arg0 - SFX_SETTINGS_BASE].volume, 0x3f, 0);
    sndFXCtrl(vid, 0x5b, lbl_3_data_8338[arg0 - SFX_SETTINGS_BASE].pan);
    return vid;
}

// .text:0x000902FC size:0x28 mapped:0x806CF390
void fn_3_902FC(void) {
    sndVolume(0, 0xA, 0xFF);
}

// .text:0x00090328 size:0x90 mapped:0x806CF3BC
void fn_3_90328(void) {
    return;
}

// .text:0x000903B8 size:0x7C mapped:0x806CF44C
void fn_3_903B8(void) {
    if (sndSeqGetValid(lbl_3_common_bss_34C58._04) != 0) {
        sndSeqVolume(0, 0xA0, lbl_3_common_bss_34C58._04, 1);
    }

    if (sndSeqGetValid(lbl_3_common_bss_34C58._08) != 0) {
        sndSeqVolume(0, 0xA0, lbl_3_common_bss_34C58._08, 1);
    }
}

// .text:0x00090434 size:0x138 mapped:0x806CF4C8
void fn_3_90434(void) {
    return;
}

// .text:0x0009056C size:0x108 mapped:0x806CF600
s32 fn_3_9056C(s32 songIndex) {
    SoundTables* tables = &lbl_3_data_8148;
    SongEntry* song;
    Struct34C58* state;
    SND_SEQID seq;
    u8 volume;

    if (g_d_GameSettings.GameModeSelected != 2) {
        song = &tables->songs[songIndex];
    } else {
        song = &tables->practiceSongs[songIndex];
    }
    state = &lbl_3_common_bss_34C58;
    if (sndSeqGetValid(state->_08) != 0) {
        sndSeqVolume(0, 0, state->_08, 1);
        return 0;
    }
    seq = sndSeqPlayEx(song->seqID, song->groupID, lbl_3_bss_1774[songIndex], 0, 0);
    volume = tables->songSettings[songIndex].volume;
    state->_08 = seq;
    lbl_800EF808.musicVolume = volume;
    sndSeqVolume(volume, 0, seq, 0);
    return 1;
}

// .text:0x00090674 size:0x88 mapped:0x806CF708
void fn_3_90674(s32 songIndex) {
    SongEntry* song = &lbl_3_data_88E0[songIndex];
    lbl_3_common_bss_34C58._04 = sndSeqPlayEx(song->seqID, song->groupID, lbl_3_bss_1774[songIndex], 0, 0);
    sndSeqVolume(lbl_3_data_830C[songIndex].volume, 0, lbl_3_common_bss_34C58._04, 0);
}

// .text:0x000906FC size:0x58 mapped:0x806CF790
void fn_3_906FC(void) {
    return;
}
