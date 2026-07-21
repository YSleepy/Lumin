#include "LQuat.h"
#include "LMathCommon.h"

#include <cmath>

namespace Lumin::Math
{
	LQuat LQuat::Static_FromEuler(float pitch, float yaw, float roll)
	{
		float cp = std::cos(pitch * 0.5f);
		float sp = std::sin(pitch * 0.5f);
		float cy = std::cos(yaw * 0.5f);
		float sy = std::sin(yaw * 0.5f);
		float cr = std::cos(roll * 0.5f);
		float sr = std::sin(roll * 0.5f);

		return {
			sp * cy * cr - cp * sy * sr,
			cp * sy * cr + sp * cy * sr,
			cp * cy * sr - sp * sy * cr,
			cp * cy * cr + sp * sy * sr
		};
	}

	LQuat LQuat::Static_FromAxisAngle(const LVec3& axis, float angleRad)
	{
		float half = angleRad * 0.5f;
		float s = std::sin(half);
		LVec3 a = axis.Normalized();
		return {a.x() * s, a.y() * s, a.z() * s, std::cos(half)};
	}

	LVec3 LQuat::RotateVec3(const LVec3& v) const
	{
		LVec3 u(x, y, z);
		float s = w;
		return u * 2.0f * u.Dot(v)
			+ v * (s * s - u.Dot(u))
			+ u.Cross(v) * 2.0f * s;
	}

	LQuat LQuat::operator*(const LQuat& q) const
	{
		return {
			w * q.x + x * q.w + y * q.z - z * q.y,
			w * q.y - x * q.z + y * q.w + z * q.x,
			w * q.z + x * q.y - y * q.x + z * q.w,
			w * q.w - x * q.x - y * q.y - z * q.z
		};
	}

	LQuat LQuat::Normalized() const
	{
		float len = std::sqrt(x * x + y * y + z * z + w * w);
		if (len < EPSILON)
			return Static_Identity();
		return {x / len, y / len, z / len, w / len};
	}

	LMat4 LQuat::ToMat4() const
	{
		float xx = x * x, yy = y * y, zz = z * z;
		float xy = x * y, xz = x * z, yz = y * z;
		float wx = w * x, wy = w * y, wz = w * z;

		return
		{
			{1.f - 2.f * (yy + zz), 2.f * (xy + wz),       2.f * (xz - wy),     0.f},
			{2.f * (xy - wz),       1.f - 2.f * (xx + zz), 2.f * (yz + wx),     0.f},
			{2.f * (xz + wy),       2.f * (yz - wx),       1.f - 2.f * (xx + yy), 0.f},
			{0.f,                   0.f,                   0.f,                   1.f}
		};
	}

	LQuat LQuat::Static_Slerp(const LQuat& a, const LQuat& b, float t)
	{
		float cosTheta = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

		LQuat b2 = b;
		if (cosTheta < 0.f)
		{
			cosTheta = -cosTheta;
			b2 = {-b.x, -b.y, -b.z, -b.w};
		}

		if (cosTheta > 0.9995f)
		{
			LQuat r{
				a.x + (b2.x - a.x) * t,
				a.y + (b2.y - a.y) * t,
				a.z + (b2.z - a.z) * t,
				a.w + (b2.w - a.w) * t
			};
			return r.Normalized();
		}

		float theta = std::acos(cosTheta);
		float sinTheta = std::sin(theta);
		float wa = std::sin((1.f - t) * theta) / sinTheta;
		float wb = std::sin(t * theta) / sinTheta;

		return {
			a.x * wa + b2.x * wb,
			a.y * wa + b2.y * wb,
			a.z * wa + b2.z * wb,
			a.w * wa + b2.w * wb
		};
	}
}
