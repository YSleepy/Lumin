# EngineMath 实现指南

坐标系基础：
使用右手坐标系
面对Z轴，逆时针旋转为正。
矩阵以列主序

## 当前状态

`LVec3` 有接口但 .cpp 内部调用 `QVector3D` 做计算 — 需要改为纯数学实现。
`LMat4` 只有空壳 — 需要完整实现。
`LQuat` 全部注释 — 需要从头实现。
`LVec2`、`LVec4` 尚不存在 — 需要新增。

所有类型在 namespace `Lumin::Math` 下。

---

## 文件清单

```
EngineMath/
├── LMathCommon.h    # 常量 + 工具函数
├── LVec2.h          # 2D 向量 (header-only)
├── LVec3.h          # 3D 向量
├── LVec3.cpp
├── LVec4.h          # 4D 向量 (header-only)
├── LMat4.h          # 4x4 矩阵，列主序
├── LMat4.cpp
├── LQuat.h          # 四元数
├── LQuat.cpp
└── LTransform.h     # Transform 结构体 (从 Common.h 迁入)
```

---

## 1. LMathCommon.h

```cpp
#pragma once
#include <cmath>
#include <numbers>

namespace Lumin::Math {

constexpr float PI       = 3.14159265358979323846f;
constexpr float TWO_PI   = PI * 2.0f;
constexpr float HALF_PI  = PI * 0.5f;
constexpr float DEG2RAD  = PI / 180.0f;
constexpr float RAD2DEG  = 180.0f / PI;
constexpr float EPSILON  = 1e-6f;

inline bool ApproxEqual(float a, float b, float epsilon = EPSILON) {
    return std::abs(a - b) < epsilon;
}

inline float Clamp(float v, float lo, float hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

inline float Lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

} // namespace Lumin::Math
```

---

## 2. LVec2 (header-only)

```cpp
#pragma once
#include <cmath>

namespace Lumin::Math {

struct LVec2 {
    float x, y;

    LVec2() : x(0), y(0) {}
    explicit LVec2(float v) : x(v), y(v) {}
    LVec2(float x, float y) : x(x), y(y) {}

    // ---- 静态工厂 ----
    static LVec2 Zero()  { return {0, 0}; }
    static LVec2 One()   { return {1, 1}; }
    static LVec2 Up()    { return {0, 1}; }
    static LVec2 Right() { return {1, 0}; }

    // ---- 算术 ----
    LVec2 operator+(const LVec2& v) const { return {x+v.x, y+v.y}; }
    LVec2 operator-(const LVec2& v) const { return {x-v.x, y-v.y}; }
    LVec2 operator*(float s) const { return {x*s, y*s}; }
    LVec2 operator/(float s) const { return {x/s, y/s}; }
    LVec2 operator-() const { return {-x, -y}; }

    LVec2& operator+=(const LVec2& v) { x+=v.x; y+=v.y; return *this; }
    LVec2& operator-=(const LVec2& v) { x-=v.x; y-=v.y; return *this; }
    LVec2& operator*=(float s) { x*=s; y*=s; return *this; }
    LVec2& operator/=(float s) { x/=s; y/=s; return *this; }

    bool operator==(const LVec2& v) const { return x==v.x && y==v.y; }
    bool operator!=(const LVec2& v) const { return !(*this == v); }

    // ---- 向量运算 ----
    float Length()        const { return std::sqrt(x*x + y*y); }
    float LengthSquared() const { return x*x + y*y; }
    float Dot(const LVec2& v)    const { return x*v.x + y*v.y; }

    LVec2 Normalized() const {
        float len = Length();
        return len > 0 ? *this / len : LVec2::Zero();
    }

    // 下标访问
    float operator[](int i) const { return (&x)[i]; }
    float& operator[](int i) { return (&x)[i]; }
};

inline LVec2 operator*(float s, const LVec2& v) { return v * s; }

} // namespace Lumin::Math
```

---

## 3. LVec3（重写现有文件）

### LVec3.h

```cpp
#pragma once

namespace Lumin::Math {

struct LVec3 {
    float x, y, z;

    LVec3() : x(0), y(0), z(0) {}
    explicit LVec3(float v) : x(v), y(v), z(v) {}
    LVec3(float x, float y, float z) : x(x), y(y), z(z) {}

    // ---- 静态工厂 ----
    static LVec3 Zero()    { return {0, 0, 0}; }
    static LVec3 One()     { return {1, 1, 1}; }
    static LVec3 Up()      { return {0, 1, 0}; }
    static LVec3 Forward() { return {0, 0, -1}; }  // OpenGL convention
    static LVec3 Right()   { return {1, 0, 0}; }

    // ---- 算术 (header-only for inline) ----
    LVec3 operator+(const LVec3& v) const { return {x+v.x, y+v.y, z+v.z}; }
    LVec3 operator-(const LVec3& v) const { return {x-v.x, y-v.y, z-v.z}; }
    LVec3 operator*(float s)      const { return {x*s, y*s, z*s}; }
    LVec3 operator/(float s)      const { return {x/s, y/s, z/s}; }
    LVec3 operator-()             const { return {-x, -y, -z}; }

    LVec3& operator+=(const LVec3& v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
    LVec3& operator-=(const LVec3& v) { x-=v.x; y-=v.y; z-=v.z; return *this; }
    LVec3& operator*=(float s) { x*=s; y*=s; z*=s; return *this; }
    LVec3& operator/=(float s) { x/=s; y/=s; z/=s; return *this; }

    bool operator==(const LVec3& v) const { return x==v.x && y==v.y && z==v.z; }
    bool operator!=(const LVec3& v) const { return !(*this == v); }

    // ---- 向量运算 ----
    float Length() const;
    float LengthSquared() const { return x*x + y*y + z*z; }
    LVec3 Normalized() const;
    float Dot(const LVec3& v) const { return x*v.x + y*v.y + z*v.z; }
    LVec3 Cross(const LVec3& v) const;

    // 下标
    float operator[](int i) const { return (&x)[i]; }
    float& operator[](int i) { return (&x)[i]; }
};

inline LVec3 operator*(float s, const LVec3& v) { return v * s; }

} // namespace Lumin::Math
```

### LVec3.cpp（纯数学实现，删除 QVector3D）

```cpp
#include "LVec3.h"
#include "LMathCommon.h"
#include <cmath>

namespace Lumin::Math {

float LVec3::Length() const {
    return std::sqrt(x*x + y*y + z*z);
}

LVec3 LVec3::Normalized() const {
    float len = Length();
    if (len < EPSILON) return Zero();
    return *this / len;
}

LVec3 LVec3::Cross(const LVec3& v) const {
    return {
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    };
}

} // namespace Lumin::Math
```

**关键点**：千万不要在 cpp 里再 `#include <QVector3D>` — 这是去 Qt 化的第一步，cpp 里全部用纯 float 运算。

---

## 4. LVec4 (header-only)

```cpp
#pragma once
#include "LVec3.h"

namespace Lumin::Math {

struct LVec4 {
    float x, y, z, w;

    LVec4() : x(0), y(0), z(0), w(0) {}
    explicit LVec4(float v) : x(v), y(v), z(v), w(v) {}
    LVec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    LVec4(const LVec3& xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

    LVec3 xyz() const { return {x, y, z}; }

    // 算术（同 LVec2/LVec3 模式，省略）
    LVec4 operator+(const LVec4& v) const { return {x+v.x, y+v.y, z+v.z, w+v.w}; }
    LVec4 operator-(const LVec4& v) const { return {x-v.x, y-v.y, z-v.z, w-v.w}; }
    LVec4 operator*(float s) const { return {x*s, y*s, z*s, w*s}; }
    LVec4 operator/(float s) const { return {x/s, y/s, z/s, w/s}; }

    float Length() const { return std::sqrt(x*x + y*y + z*z + w*w); }
    float Dot(const LVec4& v) const { return x*v.x + y*v.y + z*v.z + w*v.w; }

    float operator[](int i) const { return (&x)[i]; }
    float& operator[](int i) { return (&x)[i]; }
};

} // namespace Lumin::Math
```

---

## 5. LMat4

### 列主序说明

```
OpenGL / GLSL 使用列主序，内存布局:
m[0]  m[4]  m[8]  m[12]    列0  列1  列2  列3
m[1]  m[5]  m[9]  m[13]
m[2]  m[6]  m[10] m[14]
m[3]  m[7]  m[11] m[15]
```

### LMat4.h

```cpp
#pragma once
#include "LVec3.h"
#include "LVec4.h"

namespace Lumin::Math {

struct LQuat; // forward declare

struct LMat4 {
    // 列主序，16 个 float
    // col i = (m[i], m[i+4], m[i+8], m[i+12])
    float m[16];

    // 构造单位矩阵
    LMat4();

    // ---- 静态工厂 ----
    static LMat4 Identity();
    static LMat4 Translate(const LVec3& pos);
    static LMat4 Rotate(float angleRad, const LVec3& axis);
    static LMat4 Rotate(const LQuat& q);
    static LMat4 Scale(const LVec3& scale);
    static LMat4 LookAt(const LVec3& eye, const LVec3& center, const LVec3& up);
    static LMat4 Perspective(float fovYDeg, float aspect, float near, float far);
    static LMat4 Ortho(float l, float r, float b, float t, float n, float f);

    // ---- 运算 ----
    LMat4 operator*(const LMat4& other) const;
    LVec4 operator*(const LVec4& v) const;

    LMat4 Transposed() const;
    LMat4 Inverted() const;

    // 提取列
    LVec4 GetColumn(int i) const { return {m[i], m[i+4], m[i+8], m[i+12]}; }
    void  SetColumn(int i, const LVec4& col);

    // 获取原始数据指针 (传给 OpenGL)
    const float* Data() const { return m; }
    float* Data() { return m; }
};

} // namespace Lumin::Math
```

### LMat4.cpp 实现要点

**单位矩阵**：
```cpp
LMat4::LMat4() {
    // 列主序单位矩阵
    // col0 col1 col2 col3
    m[0]=1; m[4]=0; m[8]=0;  m[12]=0;
    m[1]=0; m[5]=1; m[9]=0;  m[13]=0;
    m[2]=0; m[6]=0; m[10]=1; m[14]=0;
    m[3]=0; m[7]=0; m[11]=0; m[15]=1;
}
```

**Translate**：
```cpp
LMat4 LMat4::Translate(const LVec3& pos) {
    LMat4 ret; // 单位矩阵
    ret.m[12] = pos.x;
    ret.m[13] = pos.y;
    ret.m[14] = pos.z;
    return ret;
}
```

**Scale**：
```cpp
LMat4 LMat4::Scale(const LVec3& scale) {
    LMat4 ret;
    ret.m[0]  = scale.x;
    ret.m[5]  = scale.y;
    ret.m[10] = scale.z;
    return ret;
}
```

**Rotate (绕任意轴)** — 用 Rodrigues 旋转公式：
```cpp
LMat4 LMat4::Rotate(float angleRad, const LVec3& axis) {
    LVec3 a = axis.Normalized();
    float c = std::cos(angleRad);
    float s = std::sin(angleRad);
    float t = 1.0f - c;

    LMat4 ret;
    ret.m[0]  = t*a.x*a.x + c;
    ret.m[1]  = t*a.x*a.y + s*a.z;
    ret.m[2]  = t*a.x*a.z - s*a.y;
    ret.m[3]  = 0;

    ret.m[4]  = t*a.x*a.y - s*a.z;
    ret.m[5]  = t*a.y*a.y + c;
    ret.m[6]  = t*a.y*a.z + s*a.x;
    ret.m[7]  = 0;

    ret.m[8]  = t*a.x*a.z + s*a.y;
    ret.m[9]  = t*a.y*a.z - s*a.x;
    ret.m[10] = t*a.z*a.z + c;
    ret.m[11] = 0;

    ret.m[12] = ret.m[13] = ret.m[14] = 0;
    ret.m[15] = 1;

    return ret;
}
```

**Perspective**：
```cpp
LMat4 LMat4::Perspective(float fovYDeg, float aspect, float n, float f) {
    float rad = fovYDeg * DEG2RAD;
    float tanHalf = std::tan(rad * 0.5f);

    LMat4 ret{};
    ret.m[0]  = 1.0f / (aspect * tanHalf);
    ret.m[5]  = 1.0f / tanHalf;
    ret.m[10] = -(f + n) / (f - n);
    ret.m[11] = -1.0f;
    ret.m[14] = -(2.0f * f * n) / (f - n);
    ret.m[15] = 0;
    return ret;
}
```

**LookAt**：
```cpp
LMat4 LMat4::LookAt(const LVec3& eye, const LVec3& center, const LVec3& up) {
    LVec3 f = (center - eye).Normalized();  // forward
    LVec3 s = f.Cross(up).Normalized();      // side
    LVec3 u = s.Cross(f);                    // real up

    LMat4 ret;
    ret.m[0] = s.x;   ret.m[4] = s.y;   ret.m[8]  = s.z;   ret.m[12] = -s.Dot(eye);
    ret.m[1] = u.x;   ret.m[5] = u.y;   ret.m[9]  = u.z;   ret.m[13] = -u.Dot(eye);
    ret.m[2] = -f.x;  ret.m[6] = -f.y;  ret.m[10] = -f.z;  ret.m[14] = f.Dot(eye);
    ret.m[3] = 0;     ret.m[7] = 0;     ret.m[11] = 0;     ret.m[15] = 1;
    return ret;
}
```

**乘法 (矩阵 × 矩阵)** — 列主序公式：
```
C[i][j] = sum(k, A[i][k] * B[k][j])
即 C.col(j) = A * B.col(j)
```
```cpp
LMat4 LMat4::operator*(const LMat4& other) const {
    LMat4 ret;
    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            ret.m[col*4 + row] =
                m[row]    * other.m[col*4]     +   // A[row][0] * B[0][col]
                m[row+4]  * other.m[col*4+1]   +   // A[row][1] * B[1][col]
                m[row+8]  * other.m[col*4+2]   +   // A[row][2] * B[2][col]
                m[row+12] * other.m[col*4+3];       // A[row][3] * B[3][col]
        }
    }
    return ret;
}
```

**逆矩阵**：如果你不想手写 Gauss-Jordan 消元，建议用 Laplace 展开+伴随矩阵法计算 4x4 的逆。或者从网上找一个可靠的纯 C++ 实现。这里不要求从零推导，重点是**不含 Qt**。

---

## 6. LQuat

### LQuat.h

```cpp
#pragma once
#include "LVec3.h"
#include "LMat4.h"

namespace Lumin::Math {

struct LQuat {
    float x, y, z, w;  // w = cos(θ/2), (x,y,z) = sin(θ/2) * axis

    LQuat() : x(0), y(0), z(0), w(1) {}
    LQuat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    static LQuat Identity() { return {0, 0, 0, 1}; }

    // 从欧拉角 (pitch, yaw, roll) in radians
    static LQuat FromEuler(float pitch, float yaw, float roll);

    // 从轴角
    static LQuat FromAxisAngle(const LVec3& axis, float angleRad);

    // 旋转向量
    LVec3 Rotate(const LVec3& v) const;

    // 四元数乘法（旋转组合）
    LQuat operator*(const LQuat& q) const;

    // 归一化
    LQuat Normalized() const;

    // 共轭
    LQuat Conjugate() const { return {-x, -y, -z, w}; }

    // 转为旋转矩阵
    LMat4 ToMat4() const;

    // 球面线性插值
    static LQuat Slerp(const LQuat& a, const LQuat& b, float t);
};

} // namespace Lumin::Math
```

### LQuat.cpp 实现要点

**FromAxisAngle**：
```cpp
LQuat LQuat::FromAxisAngle(const LVec3& axis, float rad) {
    float half = rad * 0.5f;
    float s = std::sin(half);
    LVec3 a = axis.Normalized();
    return {a.x * s, a.y * s, a.z * s, std::cos(half)};
}
```

**Rotate vector**：
```cpp
LVec3 LQuat::Rotate(const LVec3& v) const {
    // v' = q * v * q⁻¹
    LVec3 u(x, y, z);
    float s = w;
    return u * 2.0f * u.Dot(v)
         + v * (s*s - u.Dot(u))
         + u.Cross(v) * 2.0f * s;
}
```

**乘法**：
```cpp
LQuat LQuat::operator*(const LQuat& q) const {
    return {
        w*q.x + x*q.w + y*q.z - z*q.y,
        w*q.y - x*q.z + y*q.w + z*q.x,
        w*q.z + x*q.y - y*q.x + z*q.w,
        w*q.w - x*q.x - y*q.y - z*q.z
    };
}
```

**ToMat4**：
```cpp
LMat4 LQuat::ToMat4() const {
    float xx = x*x, yy = y*y, zz = z*z;
    float xy = x*y, xz = x*z, yz = y*z;
    float wx = w*x, wy = w*y, wz = w*z;

    LMat4 ret;
    ret.m[0]  = 1 - 2*(yy + zz);
    ret.m[1]  = 2*(xy + wz);
    ret.m[2]  = 2*(xz - wy);
    ret.m[3]  = 0;

    ret.m[4]  = 2*(xy - wz);
    ret.m[5]  = 1 - 2*(xx + zz);
    ret.m[6]  = 2*(yz + wx);
    ret.m[7]  = 0;

    ret.m[8]  = 2*(xz + wy);
    ret.m[9]  = 2*(yz - wx);
    ret.m[10] = 1 - 2*(xx + yy);
    ret.m[11] = 0;

    ret.m[12] = ret.m[13] = ret.m[14] = 0;
    ret.m[15] = 1;

    return ret;
}
```

**FromEuler (pitch-yaw-roll / YXZ 顺序)**：
```cpp
LQuat LQuat::FromEuler(float pitch, float yaw, float roll) {
    float cp = std::cos(pitch*0.5f), sp = std::sin(pitch*0.5f);
    float cy = std::cos(yaw*0.5f),   sy = std::sin(yaw*0.5f);
    float cr = std::cos(roll*0.5f),  sr = std::sin(roll*0.5f);

    return {
        sp*cy*cr - cp*sy*sr,   // x
        cp*sy*cr + sp*cy*sr,   // y
        cp*cy*sr - sp*sy*cr,   // z
        cp*cy*cr + sp*sy*sr    // w
    };
}
```

**Slerp**：
```cpp
LQuat LQuat::Slerp(const LQuat& a, const LQuat& b, float t) {
    float cosTheta = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;

    LQuat b2 = b;
    if (cosTheta < 0) {
        cosTheta = -cosTheta;
        b2 = {-b.x, -b.y, -b.z, -b.w};
    }

    if (cosTheta > 0.9995f) {
        // 角度太近，线性插值
        LQuat r{a.x + (b2.x-a.x)*t, a.y + (b2.y-a.y)*t,
                a.z + (b2.z-a.z)*t, a.w + (b2.w-a.w)*t};
        return r.Normalized();
    }

    float theta = std::acos(cosTheta);
    float sinTheta = std::sin(theta);
    float wa = std::sin((1-t)*theta) / sinTheta;
    float wb = std::sin(t*theta) / sinTheta;

    return {a.x*wa + b2.x*wb, a.y*wa + b2.y*wb,
            a.z*wa + b2.z*wb, a.w*wa + b2.w*wb};
}
```

---

## 7. LTransform.h

从 `Common.h` 迁出，完全使用自研类型：

```cpp
#pragma once
#include "LVec3.h"
#include "LQuat.h"
#include "LMat4.h"

namespace Lumin {

struct LTransform {
    Math::LVec3  position = Math::LVec3::Zero();
    Math::LQuat  rotation = Math::LQuat::Identity();
    Math::LVec3  scale    = Math::LVec3::One();

    Math::LMat4 ToMatrix() const {
        Math::LMat4 t = Math::LMat4::Translate(position);
        Math::LMat4 r = rotation.ToMat4();
        Math::LMat4 s = Math::LMat4::Scale(scale);
        return t * r * s;  // TRS 顺序
    }
};

struct CameraInfo {
    Math::LMat4 ViewMatrix;
    Math::LMat4 ProjectionMatrix;
};

struct LightInfo {
    Math::LVec3 Position;
    Math::LVec3 Color;
};

} // namespace Lumin
```

---

## 实现顺序建议

1. **LMathCommon.h** — 先有 PI、DEG2RAD 等
2. **LVec2.h** — header-only，最简
3. **LVec3.h/.cpp** — 把现成的 cpp 里的 QVector3D 全删了，改为纯数学
4. **LVec4.h** — header-only
5. **LQuat.h/.cpp** — 实现完可以独立测试 `FromAxisAngle` + `Rotate`
6. **LMat4.h/.cpp** — 最后，因为依赖 LVec3 和 LQuat
7. **LTransform.h** — 全部类型到位后收尾

## 验证方式

写一个简单的 main 测试：

```cpp
#include "LVec3.h"
#include "LQuat.h"
#include "LMat4.h"
#include <cassert>
#include <cstdio>

int main() {
    using namespace Lumin::Math;

    // LVec3
    LVec3 v(1, 2, 3);
    assert(v.LengthSquared() == 14.0f);
    assert((v + v) == LVec3(2, 4, 6));

    // LQuat
    LQuat q = LQuat::FromAxisAngle(LVec3::Up(), PI * 0.5f);
    LVec3 rotated = q.Rotate(LVec3::Forward());
    // Forward(0,0,-1) 绕 Up(0,1,0) 旋转 90° 应得到 Right(1,0,0)
    printf("rotated: %f %f %f\n", rotated.x, rotated.y, rotated.z);

    // LMat4
    LMat4 t = LMat4::Translate({5, 0, 0});
    LVec4 p(1, 2, 3, 1);
    LVec4 result = t * p;
    // result 应为 (6, 2, 3, 1)
    printf("translated: %f %f %f %f\n", result.x, result.y, result.z, result.w);

    printf("All tests passed.\n");
    return 0;
}
```

---

## 后续：替换所有 Qt 数学引用

数学库就位后，需要逐个文件替换，按照这个依赖顺序（从最底层开始）：

| 优先级 | 文件 | 替换内容 |
|--------|------|---------|
| 1 | `Common.h` | `LTransform`/`CameraInfo`/`LightInfo` 改用自研类型 |
| 2 | `GActor.h/.cpp` | `QVector3D`→`LVec3`, `QQuaternion`→`LQuat`, `QMatrix4x4`→`LMat4` |
| 3 | `GSceneComponent.h/.cpp` | 同上 |
| 4 | `GCameraComponent.h/.cpp` | 同上 |
| 5 | `GLightComponent.h/.cpp` | `QVector3D`→`LVec3` |
| 6 | `GPlayerController.cpp` | 同上 |
| 7 | `LShader.h/.cpp` | `QVector2D`→`LVec2`, `QVector3D`→`LVec3`, `QMatrix4x4`→`LMat4` |
| 8 | `LMaterial.h/.cpp` | 同上 |
| 9 | `LRenderQueue.h` | `QMatrix4x4`→`LMat4` |
| 10 | `LInputManager.h/.cpp` | `QVector2D`→`LVec2` |

替换完成后，`LuminEngine` 中 `#include <QVector*>` / `#include <QMatrix4x4>` / `#include <QQuaternion>` 的数量应为 0。
