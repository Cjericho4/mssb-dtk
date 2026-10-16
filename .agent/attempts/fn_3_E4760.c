/* fn_3_E4760 NONMATCHING: only diff is a swapped r3/r4 on the two lis after PSVECScale
 * (target: lis r3,0.24 / lis r4,0.0; ours r4/r3). Same issue makes fn_3_E4658 (identical prefix)
 * unmatched at HEAD; tried inline helper, written-out, extern rodata, statement reorders, zero local.
 * Needs headers diff (CastleRotObj fields) + void fn_3_E48D0(CastleRotObj*). */
static inline void castleRotObjInit(CastleRotObj* obj) {
    RotTableEntry* entries;

    obj->control.type = 0;
    CTRLSetTranslation(&obj->control, lbl_3_data_18ED0.defs[obj->rotIdx].pos.x, 0.24f + lbl_3_data_18ED0.defs[obj->rotIdx].pos.y, lbl_3_data_18ED0.defs[obj->rotIdx].pos.z);
    PSVECScale((Vec*)&lbl_3_data_18ED0.defs[obj->rotIdx].pos, 1.0f, (Vec*)&obj->pos);
    obj->pos.y -= 0.24f;
    entries = lbl_3_data_18ED0.entries;
    CTRLSetRotation(&obj->control, 0.0f, entries[obj->rotIdx].rotValues[0], 0.0f);
    obj->curRotation = entries[obj->rotIdx].rotValues[0];
    CTRLSetScale(&obj->control, 0.2f, 0.2f, 0.2f);
    obj->scale = 0.2f;
}

void fn_3_E4760(CastleRotObj* obj) {
    castleRotObjInit(obj);
    castleRotObjAnim(obj);
    obj->shrinkTimer = 0;
    obj->unkC4 = 0;
    obj->unkC7 = 0;
    obj->unkC8 = 0;
    if (obj->unkCA != 0) {
        fn_3_65F4();
        obj->unkCA = 0;
        obj->unkC0 = 0.0f;
    }
    obj->unkC9 = 0;
}

static inline void castleRotObjAnim(CastleRotObj* obj) {
    obj->unkAC = lbl_3_bss_AE18[0];
    fn_3_B97DC(obj->unk74, (ANIMBank*)obj->unkAC);
    obj->unkB8 = obj->unk74->time;
    obj->unkCB = 0;
}
/* Note: place castleRotObjInit/castleRotObjAnim before fn_3_E4760 in the file; the
 * castleRotObjInit body is identical to fn_3_E4658 (also unmatched at HEAD for the same lis swap). */
