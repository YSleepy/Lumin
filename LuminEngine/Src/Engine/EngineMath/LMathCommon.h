#pragma once
#include <cmath>
#include <numbers>

namespace Lumin::Math {

    constexpr float PI = 3.14159265358979323846f;
    constexpr float TWO_PI = PI * 2.0f;
    constexpr float HALF_PI = PI * 0.5f;
    constexpr float DEG2RAD = PI / 180.0f;
    constexpr float RAD2DEG = 180.0f / PI;
    constexpr float EPSILON = 1e-6f;

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