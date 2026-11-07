#include "Unknown/gap_800B508C.h"
#include "math.h"
#include "Dolphin/OS/OSError.h"

// .text:0x800B508C size:0xE0
// Relocates a freshly loaded bank in place: every file offset (user data, sequence table, names,
// track arrays, key arrays, key settings and interpolation payloads) becomes a pointer.
void ANIMGet(ANIMBank* bank) {
    ANIMSequences* sequence;
    struct ANIMAnimTrack* track;
    u32 i;
    KeyFrame* keys;

    if (bank->userDataSize != 0 && bank->userData != NULL) {
        bank->userData = (void*)((u32)bank->userData + (u32)bank);
    }
    sequence = (ANIMSequences*)(bank + 1);
    track = (struct ANIMAnimTrack*)(sequence + bank->numSequences);
    keys = (KeyFrame*)(track + bank->numTracks);
    bank->animSequences = (ANIMSequences*)((u32)bank->animSequences + (u32)bank);
    for (i = 0; i < bank->numSequences; i++) {
        sequence[i].sequenceName = (char*)((u32)bank + (u32)sequence[i].sequenceName);
        sequence[i].trackArray = (struct ANIMAnimTrack*)((u32)bank + (u32)sequence[i].trackArray);
    }
    for (i = 0; i < bank->numTracks; i++) {
        track[i].keyFrames = (KeyFrame*)((u32)bank + (u32)track[i].keyFrames);
    }
    for (i = 0; i < bank->numKeyFrames; i++) {
        keys[i].setting = (char*)((u32)bank + (u32)keys[i].setting);
        keys[i].interpolation = (char*)((u32)bank + (u32)keys[i].interpolation);
    }
}

// Returns the byte width of one quantized animation value.
static inline s32 animationValueSize(u8 type) {
    switch ((s32)type) {
    case 0: case 1: return 1;
    case 2: case 3: return 2;
    case 4: return 4;
    default: return 0;
    }
}

// Converts the sampled track time to the current key interval's interpolation factor.
static inline f32 animationKeyTime(ANIMPipe* pipe, KeyFrame* current, KeyFrame* next) {
    f32 time = 0.0f;
    f32 elapsed = pipe->time - current->time;
    f32 start = current->time;
    if (elapsed == time) {
        return time;
    } else if (next->time > start) {
        time = elapsed / (next->time - start);
    } else if (pipe->currentTrack->animTime >= start) {
        time = 1.0f;
    } else {
        time = elapsed / (pipe->currentTrack->animTime - start);
    }
    return time;
}

// Applies the retail ease remap, including its negative coefficient for small ease sums.
static inline f32 easeAnimationTime(f32 time, f32 incoming, f32 outgoing) {
    f32 sum = incoming + outgoing;
    f32 coefficient;
    f32 reciprocal;
    f32 remaining;
    if (0.0f != time && 1.0f != time) {
        if (0.0f == sum) {
            return time;
        } else {
            if (sum > 1.0f) {
                reciprocal = 1.0f / sum;
                incoming *= reciprocal;
                outgoing *= reciprocal;
                coefficient = 0.5f - reciprocal;
            } else {
                coefficient = 0.5f - (1.0f / sum);
            }
            if (time < incoming) {
                time *= time * (coefficient / incoming);
            } else if (time < 1.0f - outgoing) {
                time = coefficient * (2.0f * time - incoming);
            } else {
                remaining = 1.0f - time;
                time = -(remaining * (remaining * (coefficient / outgoing)) - 1.0f);
            }
        }
    }
    return time;
}

// Blends animation quaternions along the authored spherical arc, including antipodal keys.
static inline void slerpAnimation(Quaternion* from, Quaternion* to, Quaternion* out, f32 time) {
    f32 cosine = from->w * to->w + (from->z * to->z + (from->x * to->x + from->y * to->y));
    f32 first;
    f32 second = time;
    /* FAKEMATCH: declaration order keeps the spherical angle in the retail saved register. */
    f32 step;
    f32 angle;
    f32 reciprocal;
    if (1.0f + cosine > 0.000001f) {
        if (1.0f - cosine > 0.000001f) {
            angle = (f32)acos(cosine);
            step = time * angle;
            reciprocal = 1.0f / (f32)sin(angle);
            first = reciprocal * (f32)sin(angle - step);
            second = reciprocal * (f32)sin(step);
        } else {
            first = 1.0f - time;
        }
        out->x = first * from->x + second * to->x;
        out->y = first * from->y + second * to->y;
        out->z = first * from->z + second * to->z;
        out->w = first * from->w + second * to->w;
    } else {
        out->x = -to->y;
        out->y = to->x;
        out->z = -to->w;
        out->w = to->z;
        step = 1.5707963705062866f * time;
        first = (f32)sin(1.5707963705062866f - step);
        second = (f32)sin(step);
        out->x = first * from->x + second * out->x;
        out->y = first * from->y + second * out->y;
        out->z = first * from->z + second * out->z;
        out->w = first * from->w + second * out->w;
    }
}

// Evaluates one axis while preserving the authored Bezier polynomial association.
static inline f32 bezierAnimationAxis(f32 from, f32 to, f32 outgoing, f32 incoming, f32 tripleTime, f32 inverseTime, f32 tripleSquare, f32 cube) {
    return inverseTime * (tripleSquare * (incoming + to) + inverseTime * (inverseTime * from + tripleTime * (outgoing + from))) + cube * to;
}

// Samples cubic Bezier control offsets for a three-component animation channel.
/* FAKEMATCH: volatile output preserves the retail stack scratch stores. */
static inline void bezierAnimationVector(volatile f32* result, const f32* from, const f32* to, const f32* outgoing, const f32* incoming, f32 time) {
    f32 square = time * time;
    f32 tripleTime = 3.0f * time;
    f32 cube = time * square;
    f32 inverseTime = 1.0f - time;
    f32 tripleSquare = 3.0f * square;
    s32 axis;
    for (axis = 0; axis < 3; axis++) {
        result[axis] = bezierAnimationAxis(from[axis], to[axis], outgoing[axis], incoming[axis], tripleTime, inverseTime, tripleSquare, cube);
    }
}

// Samples Hermite tangents without scaling them by the key interval duration.
/* FAKEMATCH: volatile output preserves the retail stack scratch stores. */
static inline void hermiteAnimationVector(volatile f32* result, const f32* from, const f32* to, const f32* outgoing, const f32* incoming, f32 time) {
    f32 square = time * time;
    f32 cube = square * time;
    f32 difference = 2.0f * cube - 3.0f * square;
    /* FAKEMATCH: coefficient declaration order preserves the retail float register allocation. */
    f32 nextTangentWeight = -square + cube;
    f32 nextWeight = -difference;
    f32 currentWeight = 1.0f + difference;
    f32 currentTangentWeight = -(2.0f * square - time);
    s32 axis;
    currentTangentWeight = cube + currentTangentWeight;
    for (axis = 0; axis < 3; axis++) {
        result[axis] = nextTangentWeight * incoming[axis] + (currentTangentWeight * outgoing[axis] + (currentWeight * from[axis] + nextWeight * to[axis]));
    }
}

#pragma dont_inline on
// .text:0x800B516C size:0x4A0
// Spherical cubic blend: slerp(q0,q1,t) and slerp(a,b,t) are slerped again by 2t(1-t) into out.
void Squad(Quaternion *q0, Quaternion *a, Quaternion *b, Quaternion *q1, Quaternion *out, f32 t) {
    f32 dotEnds;
    f32 dotControls;
    f32 dotBlend;
    f32 antipodalSecondBlend;
    f32 angleEnds;
    f32 reciprocalEnds;
    f32 antipodalStepEnds;
    f32 controlZ;
    f32 angleControls;
    f32 reciprocalControls;
    f32 angleBlend;
    f32 antipodalFirstBlend;
    f32 stepEnds;
    f32 controlW;
    f32 stepControls;
    f32 reciprocalBlend;
    f32 antipodalStepBlend;
    f32 antipodalStepControls;
    f32 stepBlend;
    f32 endY;
    f32 controlY;
    f32 endX;
    f32 controlX;
    f32 endW;
    f32 endZ;
    f32 antipodalFirstEnds;
    f32 antipodalFirstControls;
    f32 sineEnds;
    f32 sineControls;
    f32 sineBlend;
    f32 perpendicularZ;
    f32 blend;
    f32 antipodalSecondEnds;
    f32 antipodalSecondControls;
    f32 firstWeightBlend;
    f32 firstWeightControls;
    f32 controlsZ;
    f32 controlsY;
    f32 endsW;
    f32 endsZ;
    f32 endsY;
    f32 endsX;
    f32 firstWeightEnds;
    f32 controlsW;
    f32 controlsX;
    f32 secondWeightBlend;
    f32 secondWeightEnds;
    f32 secondWeightControls;

    endY = q1->y;
    firstWeightControls = 1.0f - t;
    endX = q1->x;
    endZ = q1->z;
    endW = q1->w;
    dotEnds = (q0->w * endW) + ((q0->z * endZ) + ((q0->x * endX) + (q0->y * endY)));
    blend = 2.0f * firstWeightControls * t;
    if ((1.0f + dotEnds) > 0.000001f) {
        if ((1.0f - dotEnds) > 0.000001f) {
            angleEnds = (f32) acos(dotEnds);
            stepEnds = t * angleEnds;
            sineEnds = (f32) sin(angleEnds);
            reciprocalEnds = 1.0f / sineEnds;
            firstWeightEnds = reciprocalEnds * (f32) sin(angleEnds - stepEnds);
            secondWeightEnds = reciprocalEnds * (f32) sin(stepEnds);
        } else {
            firstWeightEnds = firstWeightControls;
            secondWeightEnds = t;
        }
        endsX = (firstWeightEnds * q0->x) + (secondWeightEnds * q1->x);
        endsY = (firstWeightEnds * q0->y) + (secondWeightEnds * q1->y);
        endsZ = (firstWeightEnds * q0->z) + (secondWeightEnds * q1->z);
        endsW = (firstWeightEnds * q0->w) + (secondWeightEnds * q1->w);
    } else {
        antipodalStepEnds = 1.5707963705062866f * t;
        antipodalFirstEnds = (f32) sin(1.5707963705062866f - antipodalStepEnds);
        antipodalSecondEnds = (f32) sin(antipodalStepEnds);
        endsX = (antipodalFirstEnds * q0->x) + (antipodalSecondEnds * -endY);
        endsY = (antipodalFirstEnds * q0->y) + (antipodalSecondEnds * endX);
        endsZ = (antipodalFirstEnds * q0->z) + (antipodalSecondEnds * -endW);
        endsW = (antipodalFirstEnds * q0->w) + (antipodalSecondEnds * endZ);
    }
    controlY = b->y;
    controlX = b->x;
    controlZ = b->z;
    controlW = b->w;
    dotControls = (a->w * controlW) + ((a->z * controlZ) + ((a->x * controlX) + (a->y * controlY)));
    if ((1.0f + dotControls) > 0.000001f) {
        if ((1.0f - dotControls) > 0.000001f) {
            angleControls = (f32) acos(dotControls);
            stepControls = t * angleControls;
            sineControls = (f32) sin(angleControls);
            reciprocalControls = 1.0f / sineControls;
            firstWeightControls = reciprocalControls * (f32) sin(angleControls - stepControls);
            secondWeightControls = reciprocalControls * (f32) sin(stepControls);
        } else {
            secondWeightControls = t;
        }
        controlsX = (firstWeightControls * a->x) + (secondWeightControls * b->x);
        controlsY = (firstWeightControls * a->y) + (secondWeightControls * b->y);
        controlsZ = (firstWeightControls * a->z) + (secondWeightControls * b->z);
        controlsW = (firstWeightControls * a->w) + (secondWeightControls * b->w);
    } else {
        antipodalStepControls = 1.5707963705062866f * t;
        antipodalFirstControls = (f32) sin(1.5707963705062866f - antipodalStepControls);
        antipodalSecondControls = (f32) sin(antipodalStepControls);
        controlsX = (antipodalFirstControls * a->x) + (antipodalSecondControls * -controlY);
        controlsY = (antipodalFirstControls * a->y) + (antipodalSecondControls * controlX);
        controlsZ = (antipodalFirstControls * a->z) + (antipodalSecondControls * -controlW);
        controlsW = (antipodalFirstControls * a->w) + (antipodalSecondControls * controlZ);
    }
    dotBlend = (endsW * controlsW) + ((endsZ * controlsZ) + ((endsX * controlsX) + (endsY * controlsY)));
    if ((1.0f + dotBlend) > 0.000001f) {
        if ((1.0f - dotBlend) > 0.000001f) {
            angleBlend = (f32) acos(dotBlend);
            stepBlend = blend * angleBlend;
            sineBlend = (f32) sin(angleBlend);
            reciprocalBlend = 1.0f / sineBlend;
            firstWeightBlend = reciprocalBlend * (f32) sin(angleBlend - stepBlend);
            secondWeightBlend = reciprocalBlend * (f32) sin(stepBlend);
        } else {
            firstWeightBlend = 1.0f - blend;
            secondWeightBlend = blend;
        }
        out->x = (firstWeightBlend * endsX) + (secondWeightBlend * controlsX);
        out->y = (firstWeightBlend * endsY) + (secondWeightBlend * controlsY);
        out->z = (firstWeightBlend * endsZ) + (secondWeightBlend * controlsZ);
        out->w = (firstWeightBlend * endsW) + (secondWeightBlend * controlsW);
        return;
    }
    perpendicularZ = -controlsW;
    antipodalStepBlend = 1.5707963705062866f * blend;
    out->x = -controlsY;
    out->y = controlsX;
    out->z = perpendicularZ;
    out->w = controlsZ;
    antipodalFirstBlend = (f32) sin(1.5707963705062866f - antipodalStepBlend);
    antipodalSecondBlend = (f32) sin(antipodalStepBlend);
    out->x = (antipodalFirstBlend * endsX) + (antipodalSecondBlend * out->x);
    out->y = (antipodalFirstBlend * endsY) + (antipodalSecondBlend * out->y);
    out->z = (antipodalFirstBlend * endsZ) + (antipodalSecondBlend * out->z);
    out->w = (antipodalFirstBlend * endsW) + (antipodalSecondBlend * out->w);
}

// .text:0x800B560C size:0x79C
// Decodes `count` quantized values (type: 0 u8, 1 s8, 2 u16, 3 s16, 4 f32) into floats, times `scale`.
void GetData(u8 type, void* src, f32* dst, u8 count, f32 scale) {
    return;
}

// .text:0x800B5DA8 size:0x634
// Samples the bone translation with hold, linear, Bezier, or eased Hermite interpolation.
#pragma dont_inline off
void DoTranslationAnimation(ANIMPipe* pipe, KeyFrame* current, KeyFrame* next) {
    Vec from;
    Vec to;
    f32 result[3];
    Vec outgoing;
    Vec incoming;
    f32 easeIn;
    f32 easeOut;
    f32 scale = 1.0f / (f32)(1 << (pipe->currentTrack->quantizeInfo & 0xF));
    s32 width;
    s32 vectorSize;
    u8 type;
    s32 offset;
    f32 time;
    u32 scaleMode;
    u32 rotationMode;
    char* payload;

    type = pipe->currentTrack->quantizeInfo >> 4;
    width = animationValueSize(type);
    vectorSize = width * 3;
    offset = 0;
    if (pipe->currentTrack->animType & ANIM_TYPE_SCALE) {
        offset = animationValueSize(type) * 3;
        if (pipe->currentTrack->animType & ANIM_TYPE_SCALE_QUAT) offset += animationValueSize(type) * 4;
    }
    if (pipe->currentTrack->animType & ANIM_TYPE_ROT_EULER) offset += vectorSize;
    if (pipe->currentTrack->animType & ANIM_TYPE_ROT_QUAT) offset += sizeof(((AnimationQuatAux*)0)->incoming);
    GetData(type, &current->setting[offset], &from.x, 3, scale);
    GetData(type, &next->setting[offset], &to.x, 3, scale);
    time = animationKeyTime(pipe, current, next);
    offset = 0;
    if (pipe->currentTrack->animType & ANIM_TYPE_SCALE) {
        scaleMode = ((s32)pipe->currentTrack->interpolationType >> 2) & 3;
        if (scaleMode == 2) offset = vectorSize * 2;
        if (scaleMode == 3) offset = vectorSize * 2 + sizeof(AnimationEase);
    }
    if (pipe->currentTrack->animType & ANIM_TYPE_ROT_QUAT) {
        rotationMode = ((s32)pipe->currentTrack->interpolationType >> 4) & 7;
        if (rotationMode == 4) offset += sizeof(AnimationQuatAux) - sizeof(AnimationEase);
        if (rotationMode == 5) offset += sizeof(AnimationQuatAux);
    } else if (pipe->currentTrack->animType & ANIM_TYPE_ROT_EULER) {
        rotationMode = ((s32)pipe->currentTrack->interpolationType >> 4) & 7;
        if (rotationMode == 2) offset += vectorSize * 2;
        /* FAKEMATCH: keep the tangent-stride and ease increments separate. */
        if (rotationMode == 3) {
            offset += vectorSize * 2;
            offset += sizeof(AnimationEase);
        }
    }
    switch (pipe->currentTrack->interpolationType & 3) {
    case 0:
        result[0] = from.x;
        result[1] = from.y;
        result[2] = from.z;
        break;
    case 1: {
        f32 inverseTime = 1.0f - time;
        result[0] = time * to.x + inverseTime * from.x;
        result[1] = time * to.y + inverseTime * from.y;
        result[2] = time * to.z + inverseTime * from.z;
        break;
    }
    case 2: {
        /* FAKEMATCH: add the channel offset to the payload before the tangent stride. */
        GetData(type, &(&current->interpolation[offset])[vectorSize], &outgoing.x, 3, scale);
        GetData(type, &next->interpolation[offset], &incoming.x, 3, scale);
        bezierAnimationVector(result, &from.x, &to.x, &outgoing.x, &incoming.x, time);
        break;
    }
    case 3: {
        payload = &(&current->interpolation[offset])[vectorSize];
        GetData(type, payload, &outgoing.x, 3, scale);
        GetData(lbl_803CBB51, &((AnimationEase*)&payload[vectorSize])->outgoing, &easeIn, 1, lbl_803CBB4C);
        payload = &next->interpolation[offset];
        GetData(type, payload, &incoming.x, 3, scale);
        GetData(lbl_803CBB51, &payload[vectorSize * 2], &easeOut, 1, lbl_803CBB4C);
        time = easeAnimationTime(time, easeIn, easeOut);
        hermiteAnimationVector(result, &from.x, &to.x, &outgoing.x, &incoming.x, time);
        break;
    }
    default:
        OSPanic(lbl_800E7D88, 0x222, lbl_800E7D94);
        break;
    }
    CTRLSetTranslation(pipe->control, result[0], result[1], result[2]);
}

#pragma dont_inline on
// .text:0x800B63DC size:0xA30
// Samples bone scale and its optional scale-axis quaternion, using the eased time for Hermite mode.
#pragma dont_inline off
void DoScaleAnimation(ANIMPipe* pipe, KeyFrame* current, KeyFrame* next, u8 mode) {
    f32 from[3];
    f32 to[3];
    f32 result[3];
    f32 outgoing[3];
    f32 incoming[3];
    AnimationDiagnostics* diagnostics = &lbl_800E7D58;
    Quaternion fromQuat = diagnostics->scaleDefaults[0];
    Quaternion toQuat = diagnostics->scaleDefaults[1];
    Quaternion resultQuat = diagnostics->scaleDefaults[2];
    f32 easeIn;
    f32 easeOut;
    f32 scale = 1.0f / (f32)(1 << (pipe->currentTrack->quantizeInfo & 0xF));
    s32 vectorSize;
    u8 type;
    f32 time;
    char* payload;

    type = pipe->currentTrack->quantizeInfo >> 4;
    vectorSize = animationValueSize(type) * 3;
    GetData(type, current->setting, from, 3, scale);
    GetData(type, next->setting, to, 3, scale);
    if (pipe->currentTrack->animType & ANIM_TYPE_SCALE_QUAT) {
        GetData(type, &current->setting[vectorSize], &fromQuat.x, 4, scale);
        GetData(type, &next->setting[vectorSize], &toQuat.x, 4, scale);
    }
    time = animationKeyTime(pipe, current, next);
    switch ((pipe->currentTrack->interpolationType >> 2) & 3) {
    case 0:
        result[0] = from[0];
        result[1] = from[1];
        result[2] = from[2];
        if (pipe->currentTrack->animType & ANIM_TYPE_SCALE_QUAT) {
            resultQuat.x = fromQuat.x;
            resultQuat.y = fromQuat.y;
            resultQuat.z = fromQuat.z;
            resultQuat.w = fromQuat.w;
        }
        break;
    case 1: {
        f32 inverseTime = 1.0f - time;
        result[0] = time * to[0] + inverseTime * from[0];
        result[1] = time * to[1] + inverseTime * from[1];
        result[2] = time * to[2] + inverseTime * from[2];
        if (pipe->currentTrack->animType & ANIM_TYPE_SCALE_QUAT) slerpAnimation(&fromQuat, &toQuat, &resultQuat, time);
        break;
    }
    case 2:
        GetData(type, &current->interpolation[vectorSize], outgoing, 3, scale);
        GetData(type, next->interpolation, incoming, 3, scale);
        bezierAnimationVector(result, from, to, outgoing, incoming, time);
        if (pipe->currentTrack->animType & ANIM_TYPE_SCALE_QUAT) slerpAnimation(&fromQuat, &toQuat, &resultQuat, time);
        break;
    case 3:
        payload = &current->interpolation[vectorSize];
        GetData(type, payload, outgoing, 3, scale);
        GetData(lbl_803CBB51, &((AnimationEase*)&payload[vectorSize])->outgoing, &easeIn, 1, lbl_803CBB4C);
        GetData(type, next->interpolation, incoming, 3, scale);
        GetData(lbl_803CBB51, &next->interpolation[vectorSize * 2], &easeOut, 1, lbl_803CBB4C);
        time = easeAnimationTime(time, easeIn, easeOut);
        hermiteAnimationVector(result, from, to, outgoing, incoming, time);
        if (pipe->currentTrack->animType & ANIM_TYPE_SCALE_QUAT) slerpAnimation(&fromQuat, &toQuat, &resultQuat, time);
        break;
    default:
        OSPanic(diagnostics->file, 0x1A8, diagnostics->unsupportedInterpolation);
        break;
    }
    CTRLSetScale(pipe->control, result[0], result[1], result[2]);
    CTRL_SetQuatUnk(pipe->control, resultQuat.x, resultQuat.y, resultQuat.z, resultQuat.w);
}

// .text:0x800B6E0C size:0x3B4
// Samples Euler rotation in degrees, wrapping linear segments across the half-turn boundary.
#pragma dont_inline off
void DoEulerAnimation(ANIMPipe* pipe, KeyFrame* current, KeyFrame* next) {
    f32 from[3];
    f32 to[3];
    f32 result[3];
    Vec outgoing;
    Vec incoming;
    AnimationDiagnostics* diagnostics = &lbl_800E7D58;
    f32 scale = 1.0f / (f32)(1 << (pipe->currentTrack->quantizeInfo & 0xF));
    s32 vectorSize;
    u8 type;
    s32 offset;
    f32 time;
    u32 scaleMode;

    type = pipe->currentTrack->quantizeInfo >> 4;
    vectorSize = animationValueSize(type) * 3;
    offset = 0;
    if (pipe->currentTrack->animType & ANIM_TYPE_SCALE) offset = vectorSize;
    GetData(type, &current->setting[offset], &from[0], 3, scale);
    GetData(type, &next->setting[offset], &to[0], 3, scale);
    time = animationKeyTime(pipe, current, next);
    offset = 0;
    if (pipe->currentTrack->animType & ANIM_TYPE_SCALE) {
        scaleMode = (pipe->currentTrack->interpolationType >> 2) & 3;
        if (scaleMode == 2) offset = vectorSize * 2;
        if (scaleMode == 3) offset = vectorSize * 2 + sizeof(AnimationEase);
    }
    switch ((pipe->currentTrack->interpolationType >> 4) & 7) {
    case 0:
        result[0] = from[0];
        result[1] = from[1];
        result[2] = from[2];
        break;
    case 1: {
        f32* nextAxis = &to[0];
        f32* currentAxis = &from[0];
        f32* resultAxis = result;
        s32 count;
        f32 difference;
        f32 inverseTime = 1.0f - time;
        for (count = 0; count < 3; count++) {
            difference = *currentAxis - *nextAxis;
            if (difference > 180.0f) *currentAxis -= 360.0f;
            else if (difference < -180.0f) *nextAxis -= 360.0f;
            *resultAxis++ = time * *nextAxis++ + inverseTime * *currentAxis++;
        }
        break;
    }
    case 2:
        /* FAKEMATCH: preserve the retail association of tangent stride and channel offset. */
        GetData(type, &(&current->interpolation[offset])[vectorSize], &outgoing.x, 3, scale);
        GetData(type, &next->interpolation[offset], &incoming.x, 3, scale);
        bezierAnimationVector(result, &from[0], &to[0], &outgoing.x, &incoming.x, time);
        break;
    case 3:
        OSPanic(diagnostics->file, 0x12D, diagnostics->unsupportedEuler);
        break;
    default:
        OSPanic(diagnostics->file, 0x130, diagnostics->unsupportedInterpolation);
        break;
    }
    CTRLSetRotation(pipe->control, result[0], result[1], result[2]);
}

// .text:0x800B71C0 size:0x558
// Samples the bone rotation quaternion using hold, slerp, or eased spherical cubic interpolation.
#pragma dont_inline off
void DoQuatAnimation(ANIMPipe* pipe, KeyFrame* current, KeyFrame* next) {
    Quaternion result;
    Quaternion from;
    Quaternion to;
    Quaternion outgoing;
    Quaternion incoming;
    f32 easeOut;
    f32 easeIn;
    u8 type = pipe->currentTrack->quantizeInfo >> 4;
    s32 vectorSize = animationValueSize(type) * 3;
    s32 settingOffset = 0;
    s32 auxiliaryOffset;
    f32 time;
    f32 easedTime;
    u32 scaleMode;
    if (pipe->currentTrack->animType & ANIM_TYPE_SCALE) {
        settingOffset = animationValueSize(type) * 3;
        if (pipe->currentTrack->animType & ANIM_TYPE_SCALE_QUAT) {
            settingOffset += animationValueSize(type) * 4;
        }
    }
    GetData(lbl_803CBB50, &current->setting[settingOffset], &from.x, 4, lbl_803CBB48);
    GetData(lbl_803CBB50, &next->setting[settingOffset], &to.x, 4, lbl_803CBB48);
    time = animationKeyTime(pipe, current, next);
    easedTime = time;
    auxiliaryOffset = 0;
    if (pipe->currentTrack->animType & ANIM_TYPE_SCALE) {
        scaleMode = (pipe->currentTrack->interpolationType >> 2) & 3;
        if (scaleMode == 2) auxiliaryOffset = vectorSize * 2;
        if (scaleMode == 3) auxiliaryOffset = vectorSize * 2 + sizeof(AnimationEase);
    }
    switch ((pipe->currentTrack->interpolationType >> 4) & 7) {
    case 5:
        GetData(lbl_803CBB51, &((AnimationQuatAux*)&next->interpolation[auxiliaryOffset])->ease.incoming, &easeOut, 1, lbl_803CBB4C);
        GetData(lbl_803CBB51, &((AnimationQuatAux*)&current->interpolation[auxiliaryOffset])->ease.outgoing, &easeIn, 1, lbl_803CBB4C);
        time = easeAnimationTime(time, easeIn, easeOut);
        easedTime = time;
        /* fallthrough */
    case 4:
        GetData(lbl_803CBB50, ((AnimationQuatAux*)&current->interpolation[auxiliaryOffset])->outgoing, &outgoing.x, 4, lbl_803CBB48);
        GetData(lbl_803CBB50, &next->interpolation[auxiliaryOffset], &incoming.x, 4, lbl_803CBB48);
        Squad(&from, &outgoing, &incoming, &to, &result, easedTime);
        break;
    case 6:
        slerpAnimation(&from, &to, &result, time);
        break;
    case 0:
        result.x = from.x;
        result.y = from.y;
        result.z = from.z;
        result.w = from.w;
        break;
    default:
        OSPanic(lbl_800E7D88, 0xE1, lbl_800E7E50);
        break;
    }
    CTRLSetQuat(pipe->control, result.x, result.y, result.z, result.w);
}
#pragma dont_inline off

// .text:0x800B7718 size:0x288
// Samples the bound track at pipe->time into the bone control, then steps time by speed
// (forwards or backwards), wrapping at the track duration when looping, clamping otherwise.
void ANIMTick(ANIMPipe* pipe, u8 mode) {
    KeyFrame* current;
    KeyFrame* next;
    KeyFrame* key;
    u8 type;
    f32 scale;

    if (pipe == NULL || pipe->currentTrack == NULL) return;
    ANIMGetKeyFrameFromTrack(pipe->currentTrack, pipe->time, &current, &next, &pipe->keyIndex);
    type = pipe->currentTrack->animType;
    if (type & ANIM_TYPE_MTX) {
        scale = 1.0f / (f32)(1 << (pipe->currentTrack->quantizeInfo & 0xF));
        key = current;
        ((f32*)key->setting)[0] *= scale;
        ((f32*)key->setting)[1] *= scale;
        ((f32*)key->setting)[2] *= scale;
        ((f32*)key->setting)[3] *= scale;
        ((f32*)key->setting)[4] *= scale;
        ((f32*)key->setting)[5] *= scale;
        ((f32*)key->setting)[6] *= scale;
        ((f32*)key->setting)[7] *= scale;
        ((f32*)key->setting)[8] *= scale;
        ((f32*)key->setting)[9] *= scale;
        ((f32*)key->setting)[10] *= scale;
        ((f32*)key->setting)[11] *= scale;
        CTRLSetMatrix(pipe->control, (MtxPtr)key->setting);
        return;
    }
    if (type & ANIM_TYPE_SCALE) {
        DoScaleAnimation(pipe, current, next, mode);
    }
    if (pipe->currentTrack->animType & ANIM_TYPE_ROT_QUAT) {
        DoQuatAnimation(pipe, current, next);
    } else if (pipe->currentTrack->animType & ANIM_TYPE_ROT_EULER) {
        DoEulerAnimation(pipe, current, next);
    }
    if (pipe->currentTrack->animType & ANIM_TYPE_TRANS) {
        DoTranslationAnimation(pipe, current, next);
    }
    pipe->previousTime = pipe->time;
    if (pipe->forward == 1) {
        pipe->time += pipe->speed;
        if (pipe->time > pipe->currentTrack->animTime) {
            if (pipe->loop) {
                pipe->time -= pipe->currentTrack->animTime;
            } else {
                pipe->time = pipe->currentTrack->animTime;
            }
        }
    } else {
        pipe->time -= pipe->speed;
        if (pipe->time < 0.0f) {
            if (pipe->loop) {
                pipe->time += pipe->currentTrack->animTime;
            } else {
                pipe->time = 0.0f;
            }
        }
    }
}

#pragma dont_inline on
// .text:0x800B79A0 size:0x30
// Attaches a track to a pipe: clears the target control, rewinds to `time` and resets the key cache.
void ANIMBind(ANIMPipe* pipe, Control* control, struct ANIMAnimTrack* track, f32 time) {
    if (track == NULL) return;
    control->type = 0;
    pipe->control = control;
    pipe->currentTrack = track;
    pipe->time = time;
    pipe->previousTime = time;
    pipe->replaceHierarchyCtrl = track->replaceHierarchyCtrl;
    pipe->keyIndex = 0;
}
#pragma dont_inline off

// .text:0x800B79D0 size:0x36C
// Binds `track` to a bone (NULL unbinds). With `blend` the current pose is saved as the blend
// source; channels the track does not animate are copied from the bone's rest-pose control.
void ACTSetBoneTrack(ActBone* bone, struct ANIMAnimTrack* track, f32 time, s32 blend) {
    u8 restType;
    f32 rest[4]; /* x, y, z, w of the rest-pose channel being copied */

    if (track == NULL) {
        if (bone->animPipe != NULL && bone->animPipe->control != NULL) {
            bone->animPipe->control->type = 0;
            bone->animPipe->currentTrack = NULL;
        }
        return;
    }
    if (bone->animPipe == NULL) {
        bone->animPipe = _OSAllocFromHeap(0x20, sizeof(ANIMPipe));
        bone->animPipe->time = 0.0f;
        bone->animPipe->previousTime = 0.0f;
        bone->animPipe->speed = 1.0f;
        bone->animPipe->currentTrack = NULL;
        bone->animPipe->control = NULL;
        bone->animPipe->replaceHierarchyCtrl = 0;
        bone->animPipe->forward = 1;
        bone->animPipe->loop = 1;
    }
    bone->animPipe->keyIndex = 0;
    if (blend != 0) {
        if (bone->animPipe->control != NULL) {
            if (bone->animPipe->control->type != 0) {
                bone->blendFromCtrl = bone->animationCtrl;
            } else {
                bone->blendFromCtrl = bone->orientationCtrl;
            }
        } else {
            bone->blendFromCtrl = bone->animationCtrl;
        }
    }
    ANIMBind(bone->animPipe, &bone->animationCtrl.control, track, time);
    if (bone->holdTranslation != 0) {
        bone->animPipe->currentTrack->interpolationType &= ~3;
    }
    restType = bone->orientationCtrl.control.type;
    if ((restType & CTRL_TRANS) && !(track->animType & ANIM_TYPE_TRANS)) {
        CTRLGetTranslation(&bone->orientationCtrl.control, &rest[0], &rest[1], &rest[2]);
        CTRLSetTranslation(&bone->animationCtrl.control, rest[0], rest[1], rest[2]);
    }
    if ((restType & CTRL_SCALE) && !(track->animType & ANIM_TYPE_SCALE)) {
        CTRLGetScale(&bone->orientationCtrl.control, &rest[0], &rest[1], &rest[2]);
        CTRLSetScale(&bone->animationCtrl.control, rest[0], rest[1], rest[2]);
        if ((restType & CTRL_SCALE_QUAT) && !(track->animType & ANIM_TYPE_SCALE_QUAT)) {
            CTRL_GetQuatUnk(&bone->orientationCtrl.control, &rest[0], &rest[1], &rest[2], &rest[3]);
        } else {
            rest[0] = 0.0f;
            rest[1] = 0.0f;
            rest[2] = 0.0f;
            rest[3] = 1.0f;
        }
        CTRL_SetQuatUnk(&bone->animationCtrl.control, rest[0], rest[1], rest[2], rest[3]);
    }
    if ((restType & CTRL_ROT_EULER) && !(track->animType & ANIM_TYPE_ROT_EULER)) {
        CTRLGetRotation(&bone->orientationCtrl.control, &rest[0], &rest[1], &rest[2]);
        CTRLSetRotation(&bone->animationCtrl.control, rest[0], rest[1], rest[2]);
    } else if ((restType & CTRL_ROT_QUAT) && !(track->animType & ANIM_TYPE_ROT_QUAT)) {
        CTRLGetQuat(&bone->orientationCtrl.control, &rest[0], &rest[1], &rest[2], &rest[3]);
        CTRLSetQuat(&bone->animationCtrl.control, rest[0], rest[1], rest[2], rest[3]);
    }
    if (blend == 0) {
        bone->blendFromCtrl = bone->animationCtrl;
    }
}
