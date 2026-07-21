#pragma once
#include "pre.h"
#include "LGameInstanceBase.h"

namespace Lumin
{
	class ENGINE_API LGameModuleBase
	{
	public:
		virtual ~LGameModuleBase();

		virtual LGameInstanceBase* CreateGameInstance() = 0;
		virtual void DestroyGameInstance(LGameInstanceBase*) = 0;
	};
}
