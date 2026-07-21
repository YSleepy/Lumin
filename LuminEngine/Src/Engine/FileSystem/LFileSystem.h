#pragma once

#include "pre.h"
#include <string>
#include <QByteArray>

namespace Lumin
{
	class ENGINE_API LFileSystem
	{
	public:
		void Init(std::string gameRootPath);
		static std::string GetEngineRootPath();
		static std::string GetEngineAssetsPath();
		// The function does not check if the path is correct
		static QByteArray LoadEngineAssetFileContents(const char* filePath);

		std::string GetGameRootPath();
		std::string GetGameAssetsPath();
	private:
		std::string m_gameRootPath;
	};

}

