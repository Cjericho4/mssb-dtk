/* fn_3_CBF80 (sta_c2.c) NONMATCHING best attempt: 8 mismatching lines.
 * Header: prototype changed to void fn_3_CBF80(struct StaC2ChainObj* obj);
 * Remaining diff: register allocation in the if-body after `bl cos` only.
 * Target keeps cos result in f1, 2.4f in f0 (fmuls f0,f0,f1), 0.15f in f2, p.z in f1.
 * Ours: cos->f2, 2.4f->f1, 0.15f->f0. Writing it as one expression
 * (p.z += 2.4f * cos(...)) fuses into fmadds; any temp form gives this reg swap.
 * Tried: temp decl in block / top, cast forms, cosf_kludge, static inline helpers,
 * statement order, decl-order brute force (720 perms). StaC2ControlExt for the
 * Control local is required for the 0xE0 frame. */
void fn_3_CBF80(StaC2ChainObj* obj) {
    StaC2ControlExt ctrl;
    Mtx m;
    Vec v;
    Vec p;
    u32 i;
    f32 t;

    v = lbl_3_rodata_24E8[0];
    v.y = -4.5f;
    ctrl.control.type = 0;
    CTRLSetRotation(&ctrl.control, 0.0f, obj->angle, 0.0f);
    CTRLBuildMatrix(&ctrl.control, m);
    PSMTXMultVec(m, &v, &v);
    v.y *= -1.0f;
    v.x += obj->pos.x;
    v.y += obj->pos.y;
    v.z += obj->pos.z;
    p = v;
    for (i = 4; i != 0; i--) {
        obj->entries[i - 1].unkC[0].x = p.x;
        obj->entries[i - 1].unkC[0].y = p.y;
        obj->entries[i - 1].unkC[0].z = p.z;
        p.y -= 2.4f;
        if (p.y - 0.15000000223517418 < 0.0) {
            t = 2.4f * (f32)cos((f32)acos((f32)(0.15000000223517418 - p.y) / 2.4f));
            p.z += t;
            p.y = 0.15f;
        }
    }
    for (i = 0; i < 4; i++) {
        obj->entries[i].unkC[1] = obj->entries[i].unkC[0];
        memset(obj->entries[i].unk24, 0, 0xC);
        memset(obj->entries[i].unk30, 0, 0xC);
    }
}
