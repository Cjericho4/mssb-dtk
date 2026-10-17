#include "menus/gap_92394.h"
extern void (*lbl_2_data_308B4[])(Rep1028Obj*);

extern void (*lbl_2_data_307F0[])(Rep1028Obj*);

extern void (*lbl_2_data_307F8[])(Rep1028Obj*);

extern void (*lbl_2_data_30804[])(Rep1028Obj*);

// .text:0x00092394 size:0x38
void fn_2_92394(Rep1028Obj* obj) {
    lbl_2_data_30804[obj->state](obj);
}

// .text:0x000923CC size:0xC
void fn_2_923CC(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x000923D8 size:0xC
void fn_2_923D8(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x000923E4 size:0x88
void fn_2_923E4(void) {
    return;
}

// .text:0x0009246C size:0x38
void fn_2_9246C(Rep1028Obj* obj) {
    lbl_2_data_307F8[obj->state](obj);
}

// .text:0x000924A4 size:0xC
void fn_2_924A4(Rep1028Obj* obj) {
    obj->state = 1;
}

// .text:0x000924B0 size:0x54
void fn_2_924B0(void) {
    return;
}

// .text:0x00092504 size:0x38
void fn_2_92504(Rep1028Obj* obj) {
    lbl_2_data_307F0[obj->state](obj);
}

// .text:0x0009253C size:0x40
void fn_2_9253C(Rep1028Obj* obj) {
    obj->callback = lbl_2_data_308B4[obj->variant];
    obj->callback(obj);
}

// .text:0x0009257C size:0xD8
void fn_2_9257C(void) {
    return;
}

// .text:0x00092654 size:0x28
void fn_2_92654(void) {
    return;
}

// .text:0x0009267C size:0x14C
void fn_2_9267C(void) {
    return;
}
