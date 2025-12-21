#pragma once
#include "LGameModuleBase.h"
#include "LProjectLoader.h"

namespace EngineRuntime
{
	class LGameBootstrap
	{
	public:
		static Lumin::LGameModuleBase* SelectGameModule(LProjectLoader* projectLoader);
	};
}
