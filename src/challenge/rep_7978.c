#include "challenge/rep_7978.h"

// .text:0x00026D28 size:0x5B4
void fn_1_26D28(Rep7978Camera* camera, u16 buttons, u16 held, u16 pressed, ChallengeAxes* axes) {
    return;
}

// .text:0x000272DC size:0x54
void fn_1_272DC(Rep7978Camera* camera, u32 mtxId) {
    GXSetProjection(camera->projection, GX_PERSPECTIVE);
    GXLoadPosMtxImm(camera->view, mtxId);
    GXSetCurrentMtx(mtxId);
}

// .text:0x00027330 size:0xA8
void fn_1_27330(Rep7978Camera* camera) {
    Vec target;
    PSVECAdd(&camera->eye, &camera->direction, &target);
    C_MTXLookAt(camera->view, &camera->eye, &camera->up, &target);
    C_MTXFrustum(camera->projection, camera->scale * (camera->top * camera->nearZ) / 1280.0f, camera->scale * (camera->bottom * camera->nearZ) / 1280.0f, camera->scale * (camera->left * camera->nearZ) / 1280.0f, camera->scale * (camera->right * camera->nearZ) / 1280.0f, camera->nearZ, camera->farZ);
}

// .text:0x000273D8 size:0x188
void fn_1_273D8(Rep7978Camera* camera) {
    Vec target;
    camera->moveSpeed = 5.0f;
    camera->turnSpeed = 120.0f;
    camera->flags = 0;
    camera->angleX = 0.0f;
    camera->angleY = 0.0f;
    camera->eye.z = 0.0f;
    camera->eye.y = 0.0f;
    camera->eye.x = 0.0f;
    camera->direction.y = 0.0f;
    camera->direction.x = 0.0f;
    camera->direction.z = 1.0f;
    camera->up.x = 0.0f;
    camera->up.y = 1.0f;
    camera->up.z = 0.0f;
    PSVECAdd(&camera->eye, &camera->direction, &target);
    C_MTXLookAt(camera->view, &camera->eye, &camera->up, &target);
    camera->width = 1.0f;
    camera->height = 1.0f;
    camera->scale = 1.0f / camera->height;
    camera->nearZ = 1.0f;
    camera->farZ = 512.0f;
    camera->top = 240.0f;
    camera->bottom = -240.0f;
    camera->left = -320.0f;
    camera->right = 320.0f;
    C_MTXFrustum(camera->projection, camera->scale * (camera->top * camera->nearZ) / 1280.0f, camera->scale * (camera->bottom * camera->nearZ) / 1280.0f, camera->scale * (camera->left * camera->nearZ) / 1280.0f, camera->scale * (camera->right * camera->nearZ) / 1280.0f, camera->nearZ, camera->farZ);
}
