#pragma once

#include "LVec3.h"
#include "LVec4.h"

#include <initializer_list>

namespace Lumin::Math
{
    struct LQuat;

    struct LMat4 {
        // 列主序: m[col][row]
        float m[4][4];

        LMat4();
        LMat4(const float arr[16]);
        LMat4(std::initializer_list<std::initializer_list<float>> rows);

        static LMat4 Static_Identity();
        LMat4& Identity();

        static LMat4 Static_Translate(const LVec3& pos);
        LMat4& Translate(const LVec3& pos);

        static LMat4 Static_Rotate(float angleRad, const LVec3& axis);
        static LMat4 Static_Rotate(const LQuat& q);
        static LMat4 Static_Scale(const LVec3& scale);
        LMat4& Scale(const LVec3& scale);

        static LMat4 Static_LookAt(const LVec3& eye, const LVec3& center, const LVec3& up);
        static LMat4 Static_Perspective(float fovYDeg, float aspect, float near, float far);
        static LMat4 Static_Ortho(float l, float r, float b, float t, float n, float f);

        LMat4 operator*(const LMat4& other) const;
        LVec4 operator*(const LVec4& v) const;

        LMat4 Transposed() const;
        LMat4 Inverted() const;

        LVec4 GetColumn(int i) const { return { m[i][0], m[i][1], m[i][2], m[i][3] }; }
        void  SetColumn(int i, const LVec4& col);

        const float* Data() const { return &m[0][0]; }
        float* Data() { return &m[0][0]; }
        void DataRowMajor(float out[16]) const;
    };
}
