#ifndef GAME_PARTICLE_SPAWN_H
#define GAME_PARTICLE_SPAWN_H

#include "UnknownHeaders.h"
#include "stl/mem.h"

typedef struct {
    s32 unk0;
    u8 _pad04[0x2C];
    f32 unk30;           /* 0x30 */
    f32 unk34;           /* 0x34 */
    u8 _pad38[0x8];
    VecXYZ pos;          /* 0x40 */
    u8 color[3];         /* 0x4C */
    u8 _pad4F;
} ParticleSpawnParams; /* size: 0x50 */

extern ParticleSpawnParams lbl_3_data_28508;
extern s32 lbl_803CBD0C;
void fn_80026998(ParticleSpawnParams* params);
s32 fn_8001B728(s32 index, s32 type, VecXYZ* out);

/* Spawn a randomly coloured particle burst at a bone of the character. */
static inline void spawnCharacterParticles(AnimationStruct* anim, s32 type) {
    VecXYZ pos;
    ParticleSpawnParams params;

    memset(&pos, 0, sizeof(VecXYZ));
    memcpy(&params, &lbl_3_data_28508, sizeof(ParticleSpawnParams));
    params.unk0 = lbl_803CBD0C;
    if (fn_8001B728(anim->unk254, type, &pos) == 0) {
        memset(&pos, 0, sizeof(VecXYZ));
        fn_8001B728(anim->unk254, 4, &pos);
    }
    memcpy(&params.pos, &pos, sizeof(VecXYZ));
    params.color[0] = rand() % 256;
    params.color[1] = rand() % 256;
    params.color[2] = rand() % 256;
    fn_80026998(&params);
}

#endif // GAME_PARTICLE_SPAWN_H
