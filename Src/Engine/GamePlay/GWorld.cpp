#include "GWorld.h"

#include <QDebug>

namespace Lumin
{
	GWorld::GWorld()
	{
		std::unique_ptr<GLevel> level = CreateEmptyLevel();
		m_currentLevel = level->m_objectId;
		m_levels.insert(std::make_pair(level->m_objectId, std::move(level)));
	}

	void GWorld::Tick(float deltaTime)
	{
		GetCurrentLevel()->Tick(deltaTime);
	}

	std::unique_ptr<GLevel> GWorld::CreateEmptyLevel()
	{
		return std::make_unique<GLevel>();
	}

	GLevel* GWorld::GetLevel(uint32_t levelId)
	{
		auto it = m_levels.find(levelId);
		if (it != m_levels.end())
		{
			return it->second.get();
		}
		qDebug("Level %u not found", levelId);
		return nullptr;
	}

	GLevel* GWorld::GetCurrentLevel()
	{
		return GetLevel(m_currentLevel);
	}
}

