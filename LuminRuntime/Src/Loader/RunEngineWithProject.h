#pragma once
#include "LEngine.h"
#include "LGameBootstrap.h"
#include "LProjectLoader.h"

#include <QCoreApplication>
#include <QSurfaceFormat>
#include <thread>

namespace EngineRuntime
{
	inline void SetupOpenGL()
	{
		QSurfaceFormat format;
		format.setRenderableType(QSurfaceFormat::OpenGL);
		format.setVersion(3, 3);  // 设置 OpenGL 版本
		format.setProfile(QSurfaceFormat::CoreProfile);  // 核心模式
		QSurfaceFormat::setDefaultFormat(format);
	}

	inline void RunEngineWithProject(EngineRuntime::LProjectLoader* loader)
	{
		using namespace EngineRuntime;
		SetupOpenGL();

		Lumin::LEngine& engine = Lumin::LEngine::GetInstance();

		Lumin::LGameModuleBase* module =
			LGameBootstrap::SelectGameModule(loader);

		Lumin::LGameInstanceBase* instance =
			module->CreateGameInstance();

		engine.SetGameInstance(instance);
		if (!engine.Init({ 1080, 960 }))
		{
			return;
		}
		std::thread engineThread(
			[&engine]()
			{
				engine.Run(); //Run内有游戏主循环
			}
		);
		QCoreApplication::exec();
		engineThread.join();
		engine.Destroy();
	}

}
