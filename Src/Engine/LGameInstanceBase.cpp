#include "LGameInstanceBase.h"

namespace Lumin
{
	void LGameInstanceBase::SetNeedToBeClosed(bool value)
	{
		m_needToBeClosed = value;
	}

	bool LGameInstanceBase::IsNeedToBeClosed() const
	{
		return m_needToBeClosed;
	}

	GLevel* LGameInstanceBase::GetCurrentLevel()
	{
		return m_world.GetCurrentLevel();
	}

	GWorld* LGameInstanceBase::GetWorld()
	{
		return &m_world;
	}

	GGameModeBase* LGameInstanceBase::GetGameMode()
	{
		return GetCurrentLevel()->GetGameMode();
	}

	GActor* LGameInstanceBase::GetDefaultActor()
	{
		return GetCurrentLevel()->GetGameMode()->defaultActor;
	}
}
