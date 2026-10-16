/* fn_3_C1004 (src/game/rep_1F58.c) NONMATCHING.
 * Control flow, search loop, timer/sfx tail all match apart from register numbering.
 * Remaining: target keeps (&lbl_3_bss_9D40 + 1) in r30 and j*16 in r29 across the first
 * memcpy (6 saved regs r26-r31) and indexes the 2nd byte / 2nd block with stbx; MWCC here
 * CSEs base+j*16 and folds +1/+0x20 into displacements (5 saved regs). Tried row-union
 * struct (ar[j]/gb[j]), flat union b/h/w with j*16 indices, and p/off locals.
 * Needs lbl_3_bss_9D40 retyped (was extern u8[0x40]; fn_3_C0F8C passes &lbl_3_bss_9D40).
 */
diff --git a/src/game/rep_1F58.c b/src/game/rep_1F58.c
index 563a769..09aff1d 100644
--- a/src/game/rep_1F58.c
+++ b/src/game/rep_1F58.c
@@ -6,7 +6,6 @@
 #include <string.h>
 
 extern GXTexObj lbl_3_bss_9D20;
-extern u8 lbl_3_bss_9D40[0x40];
 extern const f32 lbl_3_rodata_1FA8;
 
 typedef struct {
@@ -23,6 +22,27 @@ typedef struct {
 } RepC0854Slot; /* size: 0x20 */
 
 extern RepC0854Obj* lbl_3_data_174A0[2];
+
+typedef struct {
+    /* 0x00 */ u8 _pad0[0x14];
+    /* 0x14 */ u8 charIndex;
+    /* 0x15 */ u8 alpha;
+    /* 0x16 */ u8 timer;
+} RepC1004Obj;
+
+typedef union {
+    u8 b[0x40];
+    u16 h[0x20];
+    u32 w[0x10];
+} RepC1004Tex; /* 4x4 RGBA8 texture: AR block then GB block */
+
+typedef struct {
+    u8 r, g, b;
+} RepC1004Color;
+
+extern RepC1004Tex lbl_3_bss_9D40;
+extern RepC1004Color lbl_3_data_17258[2];
+
 extern RepC0854Slot lbl_3_data_17260[18];
 void fn_80027918(u8 id, f32 arg1);
 
@@ -206,13 +226,58 @@ void fn_3_C0DD8(s32 arg0, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID*
 
 // .text:0x000C0F8C size:0x78 mapped:0x80700020
 void fn_3_C0F8C(void) {
-    GXInitTexObj(&lbl_3_bss_9D20, lbl_3_bss_9D40, 4, 4, 6, 0, 0, 0);
+    GXInitTexObj(&lbl_3_bss_9D20, &lbl_3_bss_9D40, 4, 4, 6, 0, 0, 0);
     GXInitTexObjLOD(&lbl_3_bss_9D20, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
 }
 
 // .text:0x000C1004 size:0x1C8 mapped:0x80700098
 void fn_3_C1004(void) {
-    return;
+    RepC1004Obj* obj = (RepC1004Obj*)lbl_803CC1B8;
+    AnimationStruct* anim = g_hugeAnimStruct.AnimationStructPtrs[obj->charIndex];
+    s32 j;
+    u8 g;
+    u8 b;
+    u8 sfx;
+    s32 off;
+    u8* p;
+
+    j = 1;
+    do {
+        if (obj->charIndex == lbl_3_data_17260[j].charIndex) {
+            break;
+        }
+    } while (j-- != 0);
+    if (j < 0) {
+        return;
+    }
+    if (--obj->timer == 0) {
+        if (anim != NULL) {
+            anim->funcPtr_0x5c = NULL;
+        }
+        lbl_3_data_17260[j].charIndex = -1;
+        fn_800B0A14_removeQueue();
+    }
+    off = j * 16;
+    p = &lbl_3_bss_9D40.b[off];
+    p[0] = obj->alpha * obj->timer / 10;
+    lbl_3_bss_9D40.b[off + 1] = lbl_3_data_17258[j].r;
+    b = lbl_3_data_17258[j].b;
+    g = lbl_3_data_17258[j].g;
+    ((u16*)p)[1] = ((u16*)p)[0];
+    ((u32*)p)[1] = ((u32*)p)[0];
+    memcpy(p + 8, p, 8);
+    p = &lbl_3_bss_9D40.b[off + 0x20];
+    p[0] = g;
+    lbl_3_bss_9D40.b[off + 0x21] = b;
+    lbl_3_bss_9D40.h[j * 8 + 0x11] = ((u16*)p)[0];
+    lbl_3_bss_9D40.w[j * 4 + 9] = ((u32*)p)[0];
+    memcpy(&lbl_3_bss_9D40.b[off + 0x28], p, 8);
+    DCStoreRange(&lbl_3_bss_9D40, 0x40);
+    sfx = 0x18;
+    if (j != 0) {
+        sfx = 0x17;
+    }
+    fn_80027918(sfx, obj->timer / 10.0f);
 }
 
 // .text:0x000C11CC size:0x178 mapped:0x80700260
