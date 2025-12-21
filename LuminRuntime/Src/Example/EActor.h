#pragma once
#include "Engine/GamePlay/GActor.h"

namespace DefaultGameMode
{
	class EActor : public Lumin::GActor
	{
	public:
		EActor();
		void Tick(float deltaTime) override;
	};


}
