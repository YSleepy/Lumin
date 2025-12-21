#pragma once

#include "LVec3.h"
namespace Lumin::Math
{
	struct LMat4
	{
		// column-major, OpenGL friendly
		float m[16]{};
		void scale(const LVec3& vector);
		void translate(const LVec3& vector);
		void rotate(float angle, const LVec3& vector);
	};
}
