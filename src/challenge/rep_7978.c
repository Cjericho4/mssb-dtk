#include "challenge/rep_7978.h"

// .text:0x00026D28 size:0x5B4
/* FAKEMATCH: the reset helper preserves the original inline stack layout. */
static inline void resetPreviewCamera(Rep7978Camera* camera) {
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

/* Update free-camera orientation, local movement and zoom, or invoke its override. */
void fn_1_26D28(Rep7978Camera* camera, u16 buttons, u16 held, u16 pressed, ChallengeAxes* axes) {
    Mtx rotation;
    Quaternion quaternion;
    Vec movement;
    if(!camera->update || camera->update==fn_1_26D28) {
        if(held&0x10) resetPreviewCamera(camera);
        else {
            camera->angleX-=((3.1415927f*camera->turnSpeed/180.0f)*(s8)axes->bytes[2])/128.0f/60.0f;
            camera->angleY-=((3.1415927f*camera->turnSpeed/180.0f)*(s8)axes->bytes[3])/128.0f/60.0f;
            while(camera->angleX < -3.1415927f) camera->angleX+=6.2831855f;
            while(camera->angleX >= 3.1415927f) camera->angleX-=6.2831855f;
            if(camera->angleY < -3.1385248f) camera->angleY=-3.1385248f;
            else if(camera->angleY > 3.1385248f) camera->angleY=3.1385248f;
            movement.x=0; movement.y=0; movement.z=1;
            PSVECCrossProduct(&movement,&camera->up,&camera->direction);
            PSVECNormalize(&camera->direction,&camera->direction);
            C_QUATRotAxisRad(&quaternion,&camera->direction,camera->angleY);
            PSMTXQuat(rotation,&quaternion);
            PSMTXMultVec(rotation,&movement,&camera->direction);
            C_QUATRotAxisRad(&quaternion,&camera->up,camera->angleX);
            PSMTXQuat(rotation,&quaternion);
            PSMTXMultVec(rotation,&camera->direction,&camera->direction);
            movement.x=(-camera->moveSpeed*(s8)axes->bytes[0])/128.0f/60.0f;
            movement.z=(camera->moveSpeed*(s8)axes->bytes[1])/128.0f/60.0f;
            movement.y=(camera->moveSpeed*axes->bytes[4])/150.0f/60.0f;
            movement.y-=(camera->moveSpeed*axes->bytes[5])/150.0f/60.0f;
            PSMTXMultVec(rotation,&movement,&movement);
            PSVECAdd(&camera->eye,&movement,&camera->eye);
            camera->height+=(camera->width*((buttons&0x400)!=0))/60.0f;
            camera->height-=(camera->width*((buttons&0x800)!=0))/60.0f;
            camera->height=0.1f*(0.0f==camera->height)+camera->height*(0.0f!=camera->height);
            camera->scale=1.0f/camera->height;
        }
    } else camera->update(camera,buttons,held,pressed,axes);
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
