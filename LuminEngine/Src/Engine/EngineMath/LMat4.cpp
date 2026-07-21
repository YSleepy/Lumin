#include "LMat4.h"
#include "LQuat.h"

#include <algorithm>
#include <cstring>

namespace Lumin::Math
{
	LMat4::LMat4()
	{
		std::memset(m, 0, sizeof(m));
	}

	LMat4::LMat4(const float arr[16])
	{
		for (int col = 0; col < 4; ++col)
			for (int row = 0; row < 4; ++row)
				m[col][row] = arr[col * 4 + row];
	}

	LMat4::LMat4(std::initializer_list<std::initializer_list<float>> rows)
	{
		int r = 0;
		for (auto& row : rows)
		{
			int c = 0;
			for (auto& val : row)
			{
				m[c][r] = val;
				++c;
			}
			++r;
		}
	}

	LMat4 LMat4::Static_Identity()
	{
		return {
			{1.f, 0.f, 0.f, 0.f},
			{0.f, 1.f, 0.f, 0.f},
			{0.f, 0.f, 1.f, 0.f},
			{0.f, 0.f, 0.f, 1.f}
		};
	}

	LMat4& LMat4::Identity()
	{
		*this = Static_Identity();
		return *this;
	}

	LMat4 LMat4::Static_Translate(const LVec3& pos)
	{
		LMat4 ret = Static_Identity();
		ret.m[3][0] = pos.x();
		ret.m[3][1] = pos.y();
		ret.m[3][2] = pos.z();
		return ret;
	}

	LMat4& LMat4::Translate(const LVec3& pos)
	{
		return *this = Static_Translate(pos) * *this;
	}

	LMat4 LMat4::Static_Rotate(float angleRad, const LVec3& axis)
	{
		LVec3 a = axis.Normalized();
		float c = std::cos(angleRad);
		float s = std::sin(angleRad);
		float t = 1.f - c;

		LMat4 ret;
		ret.m[0][0] = t * a.x() * a.x() + c;
		ret.m[0][1] = t * a.x() * a.y() + s * a.z();
		ret.m[0][2] = t * a.x() * a.z() - s * a.y();
		ret.m[0][3] = 0.f;

		ret.m[1][0] = t * a.x() * a.y() - s * a.z();
		ret.m[1][1] = t * a.y() * a.y() + c;
		ret.m[1][2] = t * a.y() * a.z() + s * a.x();
		ret.m[1][3] = 0.f;

		ret.m[2][0] = t * a.x() * a.z() + s * a.y();
		ret.m[2][1] = t * a.y() * a.z() - s * a.x();
		ret.m[2][2] = t * a.z() * a.z() + c;
		ret.m[2][3] = 0.f;

		ret.m[3][0] = 0.f;
		ret.m[3][1] = 0.f;
		ret.m[3][2] = 0.f;
		ret.m[3][3] = 1.f;

		return ret;
	}

	LMat4 LMat4::Static_Rotate(const LQuat& q)
	{
		return q.ToMat4();
	}

	LMat4 LMat4::Static_Scale(const LVec3& scale)
	{
		LMat4 ret = Static_Identity();
		ret.m[0][0] = scale.x();
		ret.m[1][1] = scale.y();
		ret.m[2][2] = scale.z();
		return ret;
	}

	LMat4& LMat4::Scale(const LVec3& scale)
	{
		return *this = Static_Scale(scale) * *this;
	}

	LMat4 LMat4::Static_LookAt(const LVec3& eye, const LVec3& center, const LVec3& up)
	{
		LVec3 f = (center - eye).Normalized();
		LVec3 s = f.Cross(up.Normalized()).Normalized();
		LVec3 u = s.Cross(f);

		LMat4 ret;
		ret.m[0][0] = s.x();   ret.m[1][0] = s.y();   ret.m[2][0] = s.z();   ret.m[3][0] = -s.Dot(eye);
		ret.m[0][1] = u.x();   ret.m[1][1] = u.y();   ret.m[2][1] = u.z();   ret.m[3][1] = -u.Dot(eye);
		ret.m[0][2] = -f.x();  ret.m[1][2] = -f.y();  ret.m[2][2] = -f.z();  ret.m[3][2] = f.Dot(eye);
		ret.m[0][3] = 0.f;     ret.m[1][3] = 0.f;     ret.m[2][3] = 0.f;     ret.m[3][3] = 1.f;

		return ret;
	}

	LMat4 LMat4::Static_Perspective(float fovYDeg, float aspect, float n, float f)
	{
		float rad = fovYDeg * DEG2RAD;
		float tanHalf = std::tan(rad * 0.5f);

		LMat4 ret{};
		ret.m[0][0] = 1.f / (aspect * tanHalf);
		ret.m[1][1] = 1.f / tanHalf;
		ret.m[2][2] = -(f + n) / (f - n);
		ret.m[2][3] = -1.f;
		ret.m[3][2] = -(2.f * f * n) / (f - n);
		ret.m[3][3] = 0.f;
		return ret;
	}

	LMat4 LMat4::Static_Ortho(float l, float r, float b, float t, float n, float f)
	{
		LMat4 ret{};
		ret.m[0][0] = 2.f / (r - l);
		ret.m[1][1] = 2.f / (t - b);
		ret.m[2][2] = -2.f / (f - n);
		ret.m[3][0] = -(r + l) / (r - l);
		ret.m[3][1] = -(t + b) / (t - b);
		ret.m[3][2] = -(f + n) / (f - n);
		ret.m[3][3] = 1.f;
		return ret;
	}

	LMat4 LMat4::operator*(const LMat4& other) const
	{
		LMat4 ret;
		for (int col = 0; col < 4; ++col)
		{
			for (int row = 0; row < 4; ++row)
			{
				ret.m[col][row] =
					m[0][row] * other.m[col][0] +
					m[1][row] * other.m[col][1] +
					m[2][row] * other.m[col][2] +
					m[3][row] * other.m[col][3];
			}
		}
		return ret;
	}

	LVec4 LMat4::operator*(const LVec4& v) const
	{
		LVec4 ret;
		for (int col = 0; col < 4; ++col)
		{
			ret[col] = v[0] * m[col][0] + v[1] * m[col][1] + v[2] * m[col][2] + v[3] * m[col][3];
		}
		return ret;
	}

	LMat4 LMat4::Transposed() const
	{
		LMat4 ret;
		for (int col = 0; col < 4; ++col)
			for (int row = 0; row < 4; ++row)
				ret.m[row][col] = m[col][row];
		return ret;
	}

	LMat4 LMat4::Inverted() const
	{
		// TODO
		return Static_Identity();
	}

	void LMat4::SetColumn(int i, const LVec4& col)
	{
		m[i][0] = col[0];
		m[i][1] = col[1];
		m[i][2] = col[2];
		m[i][3] = col[3];
	}

	void LMat4::DataRowMajor(float out[16]) const
	{
		for (int row = 0; row < 4; ++row)
			for (int col = 0; col < 4; ++col)
				out[row * 4 + col] = m[col][row];
	}
}
