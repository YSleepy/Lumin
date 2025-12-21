#include "EGameModule.h"

#include "EGameInstance.h"

namespace DefaultGameMode
{
	EGameModule::~EGameModule()
	{
	}

	Lumin::LGameInstanceBase* EGameModule::CreateGameInstance()
	{
		return new EGameInstance();
	}

	void EGameModule::DestroyGameInstance(Lumin::LGameInstanceBase* instance)
	{
		delete instance;
	}
}
