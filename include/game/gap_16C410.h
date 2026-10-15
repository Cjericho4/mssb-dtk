#ifndef GAME_GAP_16C410_H
#define GAME_GAP_16C410_H

#include "mssbTypes.h"

typedef struct {
    u8 vol;
    u8 pan;
} StadiumSfxVolPan;

extern u16 lbl_3_data_81DC[];
extern StadiumSfxVolPan lbl_3_data_8404[][15];
extern StadiumSfxVolPan lbl_3_data_84B8[][15];

void fn_3_16C410(u8 arg0);

#endif // GAME_GAP_16C410_H
