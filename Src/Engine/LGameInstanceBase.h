#pragma once
#include "GamePlay/GWorld.h"
#include "GamePlay/GameMode/GGameModeBase.h"
#include "pre.h"

namespace Lumin
{
	class ENGINE_API LGameInstanceBase
	{
	public:
		LGameInstanceBase() = default;
		virtual ~LGameInstanceBase() = default;
		LGameInstanceBase(const LGameInstanceBase&) = delete;
		LGameInstanceBase& operator=(const LGameInstanceBase&) = delete;
		LGameInstanceBase(LGameInstanceBase&&) noexcept = default;
		LGameInstanceBase& operator=(LGameInstanceBase&&) noexcept = default;

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


