#pragma once

#include "Engine/LGameInstanceBase.h"

namespace DefaultGameMode
{
	class EGameInstance : public Lumin::LGameInstanceBase
	{
	public:
		bool Init() override;
		void Tick(float deltaTime) override;
		void Destroy() override;
	};

}
