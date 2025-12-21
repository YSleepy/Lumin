#pragma once
#include "LEngine.h"
#include "LGameBootstrap.h"
#include "LProjectLoader.h"

namespace EngineRuntime
{
	inline void RunEngineWithProject(EngineRuntime::LProjectLoader* loader)
	{
		using namespace EngineRuntime;

		Lumin::LEngine& engine = Lumin::LEngine::GetInstance();

		Lumin::LGameModuleBase* module =
			LGameBootstrap::SelectGameModule(loader);

		Lumin::LGameInstanceBase* instance =
			module->CreateGameInstance();

		engine.SetGameInstance(instance);

		engine.Init({ {1080, 960} });
		engine.Run();

		module->DestroyGameInstance(instance);

		if (loader)
			loader->DestroyGameModule();
	}

}
