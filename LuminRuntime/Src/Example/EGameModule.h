#pragma once

#include "Engine/LGameModuleBase.h"

namespace DefaultGameMode
{
	class EGameModule : public Lumin::LGameModuleBase
	{
	public:
		~EGameModule() override;
		Lumin::LGameInstanceBase* CreateGameInstance() override;
		void DestroyGameInstance(Lumin::LGameInstanceBase* instance) override;
	};
}

