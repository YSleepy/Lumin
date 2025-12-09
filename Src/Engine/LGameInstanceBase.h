#pragma once
#include "GamePlay/GWorld.h"
#include "GamePlay/GameMode/GGameModeBase.h"

namespace Lumin
{
	class LGameInstanceBase
	{
	public:
		~LGameInstanceBase() = default;
		virtual bool Init() = 0;
		virtual void Tick(float deltaTime = 0) = 0;// deltaTime is in seconds
		virtual void Destroy() = 0;

		void SetNeedToBeClosed(bool value);
		bool IsNeedToBeClosed() const;
		GLevel* GetCurrentLevel();
		GWorld* GetWorld();
		GGameModeBase* GetGameMode();
		GActor* GetDefaultActor();

	protected:
		bool m_needToBeClosed;
		GWorld m_world;
	};
}


