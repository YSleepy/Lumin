#pragma once

#include "LMat4.h"
#include "LVec3.h"

namespace Lumin::Math
{
    struct LQuat {
        // w = cos(θ/2), (x,y,z) = sin(θ/2) * axis
        float x, y, z, w;

        LQuat() : x(0), y(0), z(0), w(1) {}
        LQuat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        static LQuat Static_Identity() { return { 0, 0, 0, 1 }; }

        static LQuat Static_FromEuler(float pitch, float yaw, float roll);
        static LQuat Static_FromAxisAngle(const LVec3& axis, float angleRad);

        LVec3 RotateVec3(const LVec3& v) const;
        LQuat operator*(const LQuat& q) const;
        LQuat Normalized() const;
        LQuat Conjugate() const { return { -x, -y, -z, w }; }
        LMat4 ToMat4() const;
        static LQuat Static_Slerp(const LQuat& a, const LQuat& b, float t);
    };

}
