#include "LProjectLoader.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
#include <QDebug>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "LGameModuleBase.h"

namespace EngineRuntime
{
	LProjectLoader::LProjectLoader() = default;

	LProjectLoader::~LProjectLoader()
	{
		DestroyGameModule();

#ifdef _WIN32
		if (m_dllHandle)
		{
			FreeLibrary((HMODULE)m_dllHandle);
			m_dllHandle = nullptr;
		}
#endif
	}

	bool LProjectLoader::LoadProject(const QString& projectFilePath)
	{
		QFile file(projectFilePath);
		if (!file.open(QIODevice::ReadOnly))
		{
			qWarning() << "Failed to open project file:" << projectFilePath;
			return false;
		}

		auto json = QJsonDocument::fromJson(file.readAll()).object();

		m_projectInfo.projectName = json["ProjectName"].toString();
		m_projectInfo.gameModuleName = json["GameModule"].toString();
		m_projectInfo.gameDllPath = json["GameDLL"].toString();
		m_projectInfo.contentDir = json["ContentDir"].toString();
		m_projectInfo.startupMap = json["StartupMap"].toString();

		if (!m_projectInfo.IsValid())
		{
			qWarning() << "Invalid project file";
			return false;
		}

		return LoadGameDLL();
	}

	bool LProjectLoader::LoadGameDLL()
	{
		QString baseDir = QCoreApplication::applicationDirPath();
		QString dllPath = baseDir + "/" + m_projectInfo.gameDllPath;

#ifdef _WIN32
		HMODULE module = LoadLibraryW((LPCWSTR)dllPath.utf16());
		if (!module)
		{
			qWarning() << "Failed to load game dll:" << dllPath;
			return false;
		}

		m_dllHandle = module;

		m_createFunc = (CreateModuleFunc)GetProcAddress(module, "CreateGameModule");
		m_destroyFunc = (DestroyModuleFunc)GetProcAddress(module, "DestroyGameModule");

		if (!m_createFunc || !m_destroyFunc)
		{
			qWarning() << "Invalid game module exports";
			return false;
		}
#endif
		return true;
	}

	bool LProjectLoader::HasProject() const
	{
		return m_dllHandle != nullptr;
	}

	const LProjectInfo& LProjectLoader::GetProjectInfo() const
	{
		return m_projectInfo;
	}

	Lumin::LGameModuleBase* LProjectLoader::CreateGameModule()
	{
		if (!m_createFunc || m_gameModule)
			return m_gameModule;

		m_gameModule = m_createFunc();
		return m_gameModule;
	}

	void LProjectLoader::DestroyGameModule()
	{
		if (m_gameModule && m_destroyFunc)
		{
			m_destroyFunc(m_gameModule);
			m_gameModule = nullptr;
		}
	}
}
