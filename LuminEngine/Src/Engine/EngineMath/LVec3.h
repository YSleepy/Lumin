#pragma once

#include "LMathCommon.h"

#include <cmath>
#include <cstddef>

namespace Lumin::Math
{
	struct LVec3
	{
		float pos[3];

		LVec3() : pos{0.f, 0.f, 0.f}
		{
		}

		explicit LVec3(float v) : pos{v, v, v}
		{
		}

		LVec3(float x, float y, float z) : pos{x, y, z}
		{
		}

		static LVec3 Static_Zero() { return {0, 0, 0}; }
		static LVec3 Static_One() { return {1, 1, 1}; }

		LVec3 operator+(const LVec3& v) const { return {pos[0] + v.pos[0], pos[1] + v.pos[1], pos[2] + v.pos[2]}; }
		LVec3 operator-(const LVec3& v) const { return {pos[0] - v.pos[0], pos[1] - v.pos[1], pos[2] - v.pos[2]}; }
		LVec3 operator*(float s) const { return {pos[0] * s, pos[1] * s, pos[2] * s}; }
		LVec3 operator/(float s) const { return {pos[0] / s, pos[1] / s, pos[2] / s}; }
		LVec3 operator-() const { return {-pos[0], -pos[1], -pos[2]}; }

		LVec3& operator+=(const LVec3& v)
		{
			pos[0] += v.pos[0];
			pos[1] += v.pos[1];
			pos[2] += v.pos[2];
			return *this;
		}

		LVec3& operator-=(const LVec3& v)
		{
			pos[0] -= v.pos[0];
			pos[1] -= v.pos[1];
			pos[2] -= v.pos[2];
			return *this;
		}

		LVec3& operator*=(float s)
		{
			pos[0] *= s;
			pos[1] *= s;
			pos[2] *= s;
			return *this;
		}

		LVec3& operator/=(float s)
		{
			pos[0] /= s;
			pos[1] /= s;
			pos[2] /= s;
			return *this;
		}

		bool operator==(const LVec3& v) const
		{
			return ApproxEqual(pos[0], v.pos[0]) && ApproxEqual(pos[1], v.pos[1]) && ApproxEqual(pos[2], v.pos[2]);
		}

		bool operator!=(const LVec3& v) const { return !(*this == v); }

		float Length() const { return std::sqrt(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]); }
		float LengthSquared() const { return pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]; }

		LVec3 Normalized() const
		{
			float len = Length();
			return len > 0 ? *this / len : LVec3::Static_Zero();
		}

		float Dot(const LVec3& v) const { return pos[0] * v.pos[0] + pos[1] * v.pos[1] + pos[2] * v.pos[2]; }

		LVec3 Cross(const LVec3& v) const
		{
			return {
				pos[1] * v.pos[2] - pos[2] * v.pos[1],
				pos[2] * v.pos[0] - pos[0] * v.pos[2],
				pos[0] * v.pos[1] - pos[1] * v.pos[0]
			};
		}

		float operator[](std::ptrdiff_t i) const { return pos[i]; }
		float& operator[](std::ptrdiff_t i) { return pos[i]; }
		float x() const { return pos[0]; }
		float& x() { return pos[0]; }
		float y() const { return pos[1]; }
		float& y() { return pos[1]; }
		float z() const { return pos[2]; }
		float& z() { return pos[2]; }
	};

	inline LVec3 operator*(float s, const LVec3& v) { return v * s; }
} // namespace Lumin::Math
