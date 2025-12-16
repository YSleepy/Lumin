#include "LFileSystem.h"

#include <QCoreApplication>

namespace Lumin
{
	std::string LFileSystem::GetEngineRootPath()
	{
		return QCoreApplication::applicationDirPath().toStdString();
	}

	std::string LFileSystem::GetGameRootPath()
	{
		return std::string();
	}
}

