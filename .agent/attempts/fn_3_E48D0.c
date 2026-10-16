/* fn_3_E48D0 NONMATCHING: same lis r3/r4 swap as fn_3_E4760/fn_3_E4658 after PSVECScale. Uses castleRotObjInit from fn_3_E4760.c */
void fn_3_E48D0(CastleRotObj* obj) {
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
}
