#pragma once
#include "pre.h"
#include <string>

namespace Lumin
{
	class ENGINE_API LFileSystem
	{
	public:
		static std::string GetEngineRootPath();
		std::string GetGameRootPath();
	};

}

