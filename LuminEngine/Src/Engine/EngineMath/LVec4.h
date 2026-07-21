#pragma once

#include "LMathCommon.h"
#include "LVec3.h"

#include <cmath>
#include <cstddef>

namespace Lumin::Math
{
	struct LVec4
	{
		float pos[4];

		LVec4() : pos{0.f, 0.f, 0.f, 0.f}
		{
		}

		explicit LVec4(float v) : pos{v, v, v, v}
		{
		}

		LVec4(float x, float y, float z, float w) : pos{x, y, z, w}
		{
		}

		LVec4(const LVec3& xyz, float w) : pos{xyz.x(), xyz.y(), xyz.z(), w}
		{
		}

		static LVec4 Static_Zero() { return {0.f, 0.f, 0.f, 0.f}; }
		static LVec4 Static_One() { return {1.f, 1.f, 1.f, 1.f}; }

		LVec3 xyz() const { return {pos[0], pos[1], pos[2]}; }

		LVec4 operator+(const LVec4& v) const
		{
			return {pos[0] + v.pos[0], pos[1] + v.pos[1], pos[2] + v.pos[2], pos[3] + v.pos[3]};
		}

		LVec4 operator-(const LVec4& v) const
		{
			return {pos[0] - v.pos[0], pos[1] - v.pos[1], pos[2] - v.pos[2], pos[3] - v.pos[3]};
		}

		LVec4 operator*(float s) const { return {pos[0] * s, pos[1] * s, pos[2] * s, pos[3] * s}; }
		LVec4 operator/(float s) const { return {pos[0] / s, pos[1] / s, pos[2] / s, pos[3] / s}; }
		LVec4 operator-() const { return {-pos[0], -pos[1], -pos[2], -pos[3]}; }

		LVec4& operator+=(const LVec4& v)
		{
			pos[0] += v.pos[0];
			pos[1] += v.pos[1];
			pos[2] += v.pos[2];
			pos[3] += v.pos[3];
			return *this;
		}

		LVec4& operator-=(const LVec4& v)
		{
			pos[0] -= v.pos[0];
			pos[1] -= v.pos[1];
			pos[2] -= v.pos[2];
			pos[3] -= v.pos[3];
			return *this;
		}

		LVec4& operator*=(float s)
		{
			pos[0] *= s;
			pos[1] *= s;
			pos[2] *= s;
			pos[3] *= s;
			return *this;
		}

		LVec4& operator/=(float s)
		{
			pos[0] /= s;
			pos[1] /= s;
			pos[2] /= s;
			pos[3] /= s;
			return *this;
		}

		bool operator==(const LVec4& v) const
		{
			return ApproxEqual(pos[0], v.pos[0])
				&& ApproxEqual(pos[1], v.pos[1])
				&& ApproxEqual(pos[2], v.pos[2])
				&& ApproxEqual(pos[3], v.pos[3]);
		}

		bool operator!=(const LVec4& v) const { return !(*this == v); }

		float Length() const
		{
			return std::sqrt(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2] + pos[3] * pos[3]);
		}

		float LengthSquared() const
		{
			return pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2] + pos[3] * pos[3];
		}

		LVec4 Normalized() const
		{
			float len = Length();
			return len > 0 ? *this / len : LVec4::Static_Zero();
		}

		float Dot(const LVec4& v) const
		{
			return pos[0] * v.pos[0] + pos[1] * v.pos[1] + pos[2] * v.pos[2] + pos[3] * v.pos[3];
		}

		float operator[](std::ptrdiff_t i) const { return pos[i]; }
		float& operator[](std::ptrdiff_t i) { return pos[i]; }
		float x() const { return pos[0]; }
		float& x() { return pos[0]; }
		float y() const { return pos[1]; }
		float& y() { return pos[1]; }
		float z() const { return pos[2]; }
		float& z() { return pos[2]; }
		float w() const { return pos[3]; }
		float& w() { return pos[3]; }
	};

	inline LVec4 operator*(float s, const LVec4& v) { return v * s; }
} // namespace Lumin::Math
