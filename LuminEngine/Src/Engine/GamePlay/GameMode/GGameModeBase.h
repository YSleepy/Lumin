#pragma once
#include "GController.h"
#include "GamePlay/GActor.h"
#include "pre.h"

namespace Lumin
{
	// TODO: Inherit to Actor
	class ENGINE_API GGameModeBase
	{
	public:
		GActor* defaultActor; // default camera component
		GController* defaultController;
	};
}
