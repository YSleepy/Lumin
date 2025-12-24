#include "LFileSystem.h"

#include <QCoreApplication>

namespace Lumin
{
	void LFileSystem::Init(std::string gameRootPath)
	{
		m_gameRootPath = gameRootPath;
	}

	std::string LFileSystem::GetEngineRootPath()
	{
		return QCoreApplication::applicationDirPath().toStdString();
	}

	std::string LFileSystem::GetEngineAssetsPath()
	{
		return QCoreApplication::applicationDirPath().toStdString() + "/Assets";
	}

	std::string LFileSystem::GetGameRootPath()
	{
		return m_gameRootPath;
	}

	std::string LFileSystem::GetGameAssetsPath()
	{
		return m_gameRootPath + "/Assets";
	}
}

