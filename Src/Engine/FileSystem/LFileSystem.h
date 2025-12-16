#pragma once
#include <string>

namespace Lumin
{
	class LFileSystem
	{
	public:
		std::string GetEngineRootPath();
		std::string GetGameRootPath();
	};

}

