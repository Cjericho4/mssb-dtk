// MATCHED (fable-stuck, 2026-10-16). Kept here because the idiom is shared by the whole family:
// fn_3_C82B4 (rep_1FD8), fn_3_E4FC4 (rep_2998), fn_3_D6514/fn_3_D67CC (sta_c2), fn_3_FA3C0 (sta_c4),
// fn_3_F6C60 (sta_c5), fn_3_E763C (sta_c6) all carve the same four arrays out of one _OSAllocFromHeap block
// with the identical `mulli 0x18 / slwi 2 / slwi 1 / add r0=n*2+n*4 / add=+n*24 / add=n*4+` shape.
// The size is written in *pointer order* with sizeof() of the element types, u16 first and the
// VecXYZ pair last as `n * sizeof(VecXYZ) * 2` (the `*2` on the end is what keeps n in r4 / mulli in r3):
//     u32 n = p->memcpyCount;
//     u32 size = n * sizeof(u16) + n * sizeof(u32) + n * sizeof(u32) + n * sizeof(VecXYZ) * 2;
// Plain `n*2 + n*4 + n*4 + n*24` gives the right add tree but swaps r3/r4; any order starting with n*24
// gives the wrong tree. Pointer setup after the alloc is unchanged:
//     unk3C = (u32*)&unk48[n*2]; unk44 = unk3C + n; unk40 = (u16*)(unk44 + n);
