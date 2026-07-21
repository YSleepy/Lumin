#pragma once

#include "EngineMath/LMathCommon.h"

#include <cmath>
#include <cstddef>

namespace Lumin::Math
{
	struct LVec2
	{
		float pos[2];

		LVec2() : pos{0.f, 0.f}
		{
		}

		explicit LVec2(float v) : pos{v, v}
		{
		}

		LVec2(float x, float y) : pos{x, y}
		{
		}

		static LVec2 Static_Zero() { return {0, 0}; }
		static LVec2 Static_One() { return {1, 1}; }

		LVec2 operator+(const LVec2& v) const { return {pos[0] + v.pos[0], pos[1] + v.pos[1]}; }
		LVec2 operator-(const LVec2& v) const { return {pos[0] - v.pos[0], pos[1] - v.pos[1]}; }
		LVec2 operator*(float s) const { return {pos[0] * s, pos[1] * s}; }
		LVec2 operator/(float s) const { return {pos[0] / s, pos[1] / s}; }
		LVec2 operator-() const { return {-pos[0], -pos[1]}; }

		LVec2& operator+=(const LVec2& v)
		{
			pos[0] += v.pos[0];
			pos[1] += v.pos[1];
			return *this;
		}

		LVec2& operator-=(const LVec2& v)
		{
			pos[0] -= v.pos[0];
			pos[1] -= v.pos[1];
			return *this;
		}

		LVec2& operator*=(float s)
		{
			pos[0] *= s;
			pos[1] *= s;
			return *this;
		}

		LVec2& operator/=(float s)
		{
			pos[0] /= s;
			pos[1] /= s;
			return *this;
		}

		bool operator==(const LVec2& v) const { return ApproxEqual(pos[0], v.pos[0]) && ApproxEqual(pos[1], v.pos[1]); }
		bool operator!=(const LVec2& v) const { return !(*this == v); }

		float Length() const { return std::sqrt(pos[0] * pos[0] + pos[1] * pos[1]); }
		float LengthSquared() const { return pos[0] * pos[0] + pos[1] * pos[1]; }
		float Dot(const LVec2& v) const { return pos[0] * v.pos[0] + pos[1] * v.pos[1]; }

		LVec2 Normalized() const
		{
			float len = Length();
			return len > 0 ? *this / len : LVec2::Static_Zero();
		}

		float operator[](std::ptrdiff_t i) const { return pos[i]; }
		float& operator[](std::ptrdiff_t i) { return pos[i]; }
		float x() const { return pos[0]; }
		float& x() { return pos[0]; }
		float y() const { return pos[1]; }
		float& y() { return pos[1]; }
	};

	inline LVec2 operator*(float s, const LVec2& v) { return v * s; }
} // namespace Lumin::Math
