#pragma once
#include "GController.h"
#include "GamePlay/GActor.h"

namespace Lumin
{
	// TODO: Inherit to Actor
	class GGameModeBase
	{
	public:
		GActor* defaultActor; // default camera component
		GController* defaultController;
	};
}
