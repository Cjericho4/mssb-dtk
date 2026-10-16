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
extern f32 lbl_3_data_88AC[3];
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
void fn_3_8B718(Vec* pos, Vec* vel, Vec* dir) {
    CameraView* cam = fn_80052734(0);

    if (pos != NULL) {
        pos->x = cam->pos.x;
        pos->y = cam->pos.y;
        pos->z = cam->pos.z;
    }
    if (vel != NULL) {
        vel->x = 0.0f;
        vel->y = 0.0f;
        vel->z = 0.0f;
    }
    if (dir != NULL) {
        PSVECSubtract(&cam->target, &cam->pos, dir);
        if (PSVECMag(dir)) {
            PSVECNormalize(dir, dir);
        }
    }
}

// .text:0x0008B7DC size:0x28 mapped:0x806CA870
void fn_3_8B7DC(void) {
    sndRemoveListener(&lbl_3_common_bss_32B20);
}

static inline void removeAllEmitters(void) {
    s32 i;

    for (i = 0; i < SOUND_EMITTER_COUNT; i++) {
        if (lbl_3_common_bss_32B20.emitterActive[i] != 0) {
            if (sndCheckEmitter(&lbl_3_common_bss_32B20.emitters[i]) != 0) {
                sndRemoveEmitter(&lbl_3_common_bss_32B20.emitters[i]);
            }
            lbl_3_common_bss_32B20.emitterActive[i] = 0;
        }
    }
}

// .text:0x0008B804 size:0x8C mapped:0x806CA898
void fn_3_8B804(void) {
    s32 i;

    for (i = 0; i < SOUND_EMITTER_COUNT; i++) {
        if (lbl_3_common_bss_32B20.emitterActive[i] != 0) {
            if (sndCheckEmitter(&lbl_3_common_bss_32B20.emitters[i]) != 0) {
                sndRemoveEmitter(&lbl_3_common_bss_32B20.emitters[i]);
            }
            lbl_3_common_bss_32B20.emitterActive[i] = 0;
        }
    }
}

// .text:0x0008B890 size:0xD4 mapped:0x806CA924
void fn_3_8B890(s32 idx) {
    SoundEmitterSlot* em;

    if (idx < 0 || idx >= SOUND_EMITTER_COUNT || lbl_3_common_bss_32B20.emitterActive[idx] == 0) {
        return;
    }
    em = &lbl_3_common_bss_32B20.emitters[idx];
    if (sndCheckEmitter(em) != 0) {
        VecXYZ pos = {0.0f, 0.0f, 0.0f};
        VecXYZ dir = {0.0f, 0.0f, 1.0f};
        sndUpdateEmitter(em, &pos, &dir, 0, NULL);
        sndRemoveEmitter(em);
    }
}

// .text:0x0008B964 size:0x58 mapped:0x806CA9F8
void fn_3_8B964(VecXYZ* pos, VecXYZ* vel, VecXYZ* orient) {
    if (lbl_3_common_bss_32B20.field_0x8 != 0) {
        sndUpdateListener(&lbl_3_common_bss_32B20, pos, vel, orient, &lbl_3_data_8D70, 0x7F, 0);
    }
}

// .text:0x0008B9BC size:0xA4 mapped:0x806CAA50
void fn_3_8B9BC(VecXYZ* pos) {
    VecXYZ heading;
    VecXYZ dir;

    heading.x = 0.0f;
    heading.y = 0.0f;
    heading.z = -1.0f;
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 0.0f;
    sndRemoveListener(&lbl_3_common_bss_32B20);
    sndAddListener(&lbl_3_common_bss_32B20, pos, &dir, &heading, &lbl_3_data_8D70,
                   lbl_3_data_88AC[0], lbl_3_data_88AC[0], lbl_3_data_88AC[0], 1, 0x7F, NULL);
}

typedef struct SoundEmitterDef {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 z;
    /* 0x0C */ s32 maxDis;
    /* 0x10 */ s32 comp;
    /* 0x14 */ s32 maxVol;
    /* 0x18 */ s32 minVol;
    /* 0x1C */ s32 flags[7];
    /* 0x38 */ u8 _pad38[0x3C - 0x38];
} SoundEmitterDef; /* size: 0x3C */

u32 sndAddEmitter(SoundEmitterSlot* em, VecXYZ* pos, VecXYZ* dir, f32 maxDis, f32 comp, u32 flags, u16 fxid, u8 maxVol, u8 minVol, struct SND_ROOM* room);

extern SoundEmitterDef lbl_3_data_8974[];
extern VecXYZ lbl_3_data_8D7C;

// .text:0x0008BA60 size:0x164 mapped:0x806CAAF4
void fn_3_8BA60(s32 emitterIdx, VecXYZ* pos, VecXYZ* dir) {
    VecXYZ tmp;
    SoundEmitterSlot* em;
    u8 sfx;

    if (emitterIdx < 0 || emitterIdx >= SOUND_EMITTER_COUNT || lbl_3_common_bss_32B20.emitterActive[emitterIdx] == 0) {
        return;
    }
    em = &lbl_3_common_bss_32B20.emitters[emitterIdx];
    if (sndCheckEmitter(em) == 0) {
        lbl_3_common_bss_32B20.emitterActive[emitterIdx] = 0;
        return;
    }
    sfx = lbl_3_common_bss_32B20.emitterSfx[emitterIdx];
    if (pos == NULL) {
        pos = &tmp;
        tmp.x = lbl_3_data_8974[sfx].x / 100000.0f;
        tmp.y = lbl_3_data_8974[sfx].y / 100000.0f;
        tmp.z = lbl_3_data_8974[sfx].z / 100000.0f;
    }
    if (dir == NULL) {
        dir = &lbl_3_data_8D7C;
    }
    sndUpdateEmitter(em, pos, dir, lbl_3_data_8974[sfx].maxVol, NULL);
}

// .text:0x0008BBC4 size:0x230 mapped:0x806CAC58
s32 fn_3_8BBC4(s32 soundID, VecXYZ* pos, VecXYZ* dir, s32 sfx) {
    VecXYZ tmp;
    s32 i;

    for (i = 0; i < SOUND_EMITTER_COUNT; i++) {
        if (lbl_3_common_bss_32B20.emitterActive[i] == 0 || sndCheckEmitter(&lbl_3_common_bss_32B20.emitters[i]) == 0) {
            lbl_3_common_bss_32B20.emitterSfx[i] = sfx;
            lbl_3_common_bss_32B20.emitterActive[i] = 1;
            lbl_3_common_bss_32B20.emitterUnk2098[i] = 0;
            if (pos == NULL) {
                pos = &tmp;
                tmp.x = lbl_3_data_8974[sfx].x / 100000.0f;
                tmp.y = lbl_3_data_8974[sfx].y / 100000.0f;
                tmp.z = lbl_3_data_8974[sfx].z / 100000.0f;
            }
            if (dir == NULL) {
                dir = &lbl_3_data_8D7C;
            }
            sndAddEmitter(&lbl_3_common_bss_32B20.emitters[i], pos, dir,
                          lbl_3_data_8974[sfx].maxDis / 100000.0f, lbl_3_data_8974[sfx].comp / 100000.0f,
                          lbl_3_data_8974[sfx].flags[0] | lbl_3_data_8974[sfx].flags[1] | lbl_3_data_8974[sfx].flags[2] |
                              lbl_3_data_8974[sfx].flags[3] | lbl_3_data_8974[sfx].flags[4] | lbl_3_data_8974[sfx].flags[5] |
                              lbl_3_data_8974[sfx].flags[6],
                          soundID, lbl_3_data_8974[sfx].maxVol, lbl_3_data_8974[sfx].minVol, NULL);
            return i;
        }
    }
    if (i == SOUND_EMITTER_COUNT) {
        OSPanic("m_sound.c", 0xE4C, "No Empty Emitter");
    }
    return -1;
}

// .text:0x0008BDF4 size:0x98 mapped:0x806CAE88
void fn_3_8BDF4(void) {
    removeAllEmitters();
    sndRemoveListener(&lbl_3_common_bss_32B20);
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
    CameraView* cam;
    Vec pos;
    Vec vel;
    Vec dir;

    fn_3_8CD74();
    cam = fn_80052734(0);
    pos.x = cam->pos.x;
    pos.y = cam->pos.y;
    pos.z = cam->pos.z;
    vel.x = 0.0f;
    vel.y = 0.0f;
    vel.z = 0.0f;
    PSVECSubtract(&cam->target, &cam->pos, &dir);
    if (PSVECMag(&dir)) {
        PSVECNormalize(&dir, &dir);
    }
    if (lbl_3_common_bss_32B20.field_0x8 != 0) {
        sndUpdateListener(&lbl_3_common_bss_32B20, (VecXYZ*)&pos, (VecXYZ*)&vel, (VecXYZ*)&dir, &lbl_3_data_8D70, 0x7F, 0);
    }
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
u32 fn_3_8FF5C(s32 soundID, f32 x, f32 y, f32 z) {
    s32 screenX;
    s32 screenY;
    s32 pan;
    SND_VOICEID vid;

    pan = 0x3F;
    if (lbl_800EF808.soundMode == 1) {
        fn_3_1650C(&screenX, &screenY, 1, x, -y, z);
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
extern u16 lbl_3_data_81FC[57];
extern u8 lbl_3_data_84F4[57];

void fn_3_90064(s32 soundID) {
    s32 i;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        OSPanic("m_sound.c", 0x402, "no mini game");
    }
    for (i = 0; i < 57; i++) {
        if (soundID == lbl_3_data_81FC[i]) {
            break;
        }
    }
    if (i == 57) {
        OSPanic("m_sound.c", 0x40D, "no entry mini_se_no");
    }
    sndFXStartEx(soundID, lbl_3_data_84F4[i], 0x3F, 0);
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
void fn_3_90328(s32 time) {
    if (time < 0) {
        time = 3000;
    }
    if (sndSeqGetValid(lbl_3_common_bss_34C58._04) != 0) {
        sndSeqVolume(0, time, lbl_3_common_bss_34C58._04, 1);
    }

    if (sndSeqGetValid(lbl_3_common_bss_34C58._08) != 0) {
        sndSeqVolume(0, time, lbl_3_common_bss_34C58._08, 1);
    }
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
void fn_800A86B4(s32 arg0);
void fn_800A88C0(void);
void fn_800A8B78(void);

void fn_3_90434(void) {
    Struct34C58* ptr;
    s32 i;

    fn_800A86B4(3);
    fn_800A88C0();
    fn_800A8B78();
    ptr = &lbl_3_common_bss_34C58;
    if (sndSeqGetValid(ptr->_04) != 0) {
        sndSeqVolume(0, 0, ptr->_04, 1);
    }
    ptr = &lbl_3_common_bss_34C58;
    if (sndSeqGetValid(ptr->_08) != 0) {
        sndSeqVolume(0, 0, ptr->_08, 1);
    }
    for (i = 0; i < 3; i++) {
        if (lbl_3_common_bss_34C58.fxVoices[i] != (u32)-1) {
            sndFXKeyOff(lbl_3_common_bss_34C58.fxVoices[i]);
            lbl_3_common_bss_34C58.fxVoices[i] = -1;
        }
    }
    removeAllEmitters();
    sndRemoveListener(&lbl_3_common_bss_32B20);
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
