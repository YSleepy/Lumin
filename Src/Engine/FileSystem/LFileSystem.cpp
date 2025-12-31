#include "LFileSystem.h"

#include <QCoreApplication>
#include <QFile>

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

	QByteArray LFileSystem::LoadEngineAssetFileContents(const char* filePath)
	{
		std::string path = GetEngineAssetsPath() + filePath;
		QString qPath = QString::fromStdString(path);
		QFile file(qPath);
		if (!file.open(QIODevice::ReadOnly))
		{
			qDebug() << "Failed to open file:" << qPath;
		}
		return file.readAll();
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

