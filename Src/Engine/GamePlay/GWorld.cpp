#include "GWorld.h"

#include <QDebug>

namespace Lumin
{
	GWorld::GWorld()
	{
		GLevel* level = CreateEmptyLevel();
		m_currentLevel = level->m_objectId;
		//m_levels.insert(std::make_pair(level->m_objectId, std::move(level)));
		m_levels.emplace(level->m_objectId, level);
	}

	void GWorld::Tick(float deltaTime)
	{
		GetCurrentLevel()->Tick(deltaTime);
	}

	GLevel* GWorld::CreateEmptyLevel()
	{
		return new GLevel();
	}

	GLevel* GWorld::GetLevel(uint32_t levelId)
	{
		auto it = m_levels.find(levelId);
		if (it != m_levels.end())
		{
			return it->second;
		}
		qDebug("Level %u not found", levelId);
		return nullptr;
	}

	GLevel* GWorld::GetCurrentLevel()
	{
		return GetLevel(m_currentLevel);
	}

	std::vector<LightInfo> GWorld::GetCurrentLevelLightsInfo()
	{
		return GetCurrentLevel()->CollectLightsInfo();
	}
}

