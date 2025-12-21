#pragma once
#include <memory>
#include <QString>

#include "LProjectInfo.h"
#include "LGameModuleBase.h"

namespace EngineRuntime
{
	class LProjectLoader
	{
	public:
		LProjectLoader();
		~LProjectLoader();
		// 加载项目文件
		bool LoadProject(const QString& projectFilePath);
		// 是否加载成功
		bool HasProject() const;
		// 获取项目信息
		const LProjectInfo& GetProjectInfo() const;
		// GameModule 生命周期
		Lumin::LGameModuleBase* CreateGameModule();
		void DestroyGameModule();
	private:
		bool LoadGameDLL();
	private:
		LProjectInfo m_projectInfo;

		void* m_dllHandle = nullptr;
		Lumin::LGameModuleBase* m_gameModule = nullptr;

		using CreateModuleFunc = Lumin::LGameModuleBase * (*)();
		using DestroyModuleFunc = void (*)(Lumin::LGameModuleBase*);

		CreateModuleFunc m_createFunc = nullptr;
		DestroyModuleFunc m_destroyFunc = nullptr;
	};
}
