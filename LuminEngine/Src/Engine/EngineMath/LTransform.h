#pragma once

#include "LQuat.h"
#include "LVec3.h"

namespace Lumin::Math
{
	struct LTransform
	{
		LVec3 location = LVec3::Static_Zero();
		LQuat rotation;
        LVec3 scale = LVec3::Static_One();
	};
}
