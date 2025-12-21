#pragma once

namespace Lumin::Math
{
	struct LVec3
	{
		float x, y, z;

		LVec3();
		LVec3(float x_, float y_, float z_);

		LVec3 operator+(const LVec3& rhs) const;
		LVec3 operator-(const LVec3& rhs) const;
		LVec3 operator*(float scalar) const;

		float Length() const;
		LVec3 Normalized() const;

		static float Dot(const LVec3& a, const LVec3& b);
		static LVec3 Cross(const LVec3& a, const LVec3& b);
	};
}
