#pragma once
#include "pre.h"
#include <string>

namespace Lumin
{
	class ENGINE_API LFileSystem
	{
	public:
		void Init(std::string gameRootPath);
		static std::string GetEngineRootPath();
		static std::string GetEngineAssetsPath();
		std::string GetGameRootPath();
		std::string GetGameAssetsPath();
	private:
		std::string m_gameRootPath;
	};

}

