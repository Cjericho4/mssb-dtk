/* fn_3_1048E0 NONMATCHING (rep_3090.c).
 * Logic/stack layout match. Remaining diff: target loads &lbl_3_data_1C0A8 once into r31
 * (lis r8 before stmw; stmw r26) and uses addi r4,r31,0x4f44/0x4f50/0x4f5c for lbl_3_data_20FEC/20FF8/21004.
 * That is MWCC same-TU static-data addressing (the three Vecs are file statics in .data);
 * with extern symbols MWCC re-materialises lis/addi per use (local pointer gets const-propagated).
 * Needs header changes: Rep3090CamCalc/Rep3090CamOut/Rep3090Data_1C0A8 typedefs in rep_3090.h, and
 * fn_3_104B3C(s32,s32,s32,s32,Rep3090CamCalc*) prototype. */
// diff --git a/include/game/rep_3090.h b/include/game/rep_3090.h
// index fc26b84..4e82baa 100644
// --- a/include/game/rep_3090.h
// +++ b/include/game/rep_3090.h
// @@ -86,12 +86,48 @@ void fn_3_1040D8(void);
//  void fn_3_104338(void);
//  void fn_3_1045A8(void);
//  void fn_3_104740(void);
// -void fn_3_1048E0(void);
//  void fn_3_104A3C(Vec *dst, const Mtx44 mtx);
//  void fn_3_104A88(Vec *dst, Mtx44 mtx);
//  void fn_3_104AD4(Vec *dst, Mtx44 mtx);
//  void fn_3_104B20(VecXYZ* dst, SourceObj_104B20* src);
// -void fn_3_104B3C(void);
// +typedef struct Rep3090CamCalc {
// +    /* 0x00 */ Mtx44 mtx;
// +    /* 0x40 */ f32 unk40;
// +    /* 0x44 */ u8 _pad44[0x4C - 0x44];
// +    /* 0x4C */ f32 unk4C;
// +    /* 0x50 */ u8 _pad50[0x58 - 0x50];
// +    /* 0x58 */ Vec pos;
// +    /* 0x64 */ Vec target;
// +    /* 0x70 */ Vec up;
// +    /* 0x7C */ f32 unk7C;
// +    /* 0x80 */ f32 unk80;
// +    /* 0x84 */ u8 unk84;
// +} Rep3090CamCalc; /* size: 0x88 */
// +
// +typedef struct Rep3090CamOut {
// +    /* 0x00 */ Vec pos;
// +    /* 0x0C */ Vec target;
// +    /* 0x18 */ Vec dirA;
// +    /* 0x24 */ Vec dirB;
// +    /* 0x30 */ Vec dirC;
// +    /* 0x3C */ f32 unk3C;
// +    /* 0x40 */ Vec up;
// +    /* 0x4C */ f32 unk4C;
// +    /* 0x50 */ f32 unk50;
// +    /* 0x54 */ u8 unk54;
// +} Rep3090CamOut;
// +
// +/* .data block starting at 0x1C0A8 (accessed via a single base). */
// +typedef struct Rep3090Data_1C0A8 {
// +    /* 0x0000 */ u8 _pad0[0x4F44];
// +    /* 0x4F44 */ Vec dirA; /* lbl_3_data_20FEC */
// +    /* 0x4F50 */ Vec dirB; /* lbl_3_data_20FF8 */
// +    /* 0x4F5C */ Vec dirC; /* lbl_3_data_21004 */
// +} Rep3090Data_1C0A8;
// +extern Rep3090Data_1C0A8 lbl_3_data_1C0A8;
// +
// +void fn_3_104B3C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Rep3090CamCalc* calc);
// +void fn_3_1048E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Rep3090CamOut* out);
//  void fn_3_1054CC(void);
//  void fn_3_1054D0(void);
//  // Struct for fn_3_105BD8
void fn_3_1048E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Rep3090CamOut* out) {
    Rep3090Data_1C0A8* data = &lbl_3_data_1C0A8;
    Rep3090CamCalc calc;
    Vec dirB;
    Vec dirC;

    memset(&calc, 0, sizeof(Rep3090CamCalc));
    calc.unk40 = calc.mtx[0][0] = calc.mtx[1][1] = calc.mtx[2][2] = calc.mtx[3][3] = 1.0f;
    fn_3_104B3C(arg0, arg1, arg2, arg3, &calc);
    memcpy(&out->pos, &calc.pos, sizeof(Vec));
    memcpy(&out->target, &calc.target, sizeof(Vec));
    memcpy(&out->up, &calc.up, sizeof(Vec));
    out->unk3C = calc.unk4C;
    PSMTX44MultVec(calc.mtx, &data->dirA, &out->dirA);
    PSVECNormalize(&out->dirA, &out->dirA);
    dirB = out->dirB;
    PSMTX44MultVec(calc.mtx, &data->dirB, &dirB);
    PSVECNormalize(&dirB, &dirB);
    dirC = out->dirC;
    PSMTX44MultVec(calc.mtx, &data->dirC, &dirC);
    PSVECNormalize(&dirC, &dirC);
    out->unk4C = calc.unk7C;
    out->unk50 = calc.unk80;
    out->unk54 = calc.unk84;
}
