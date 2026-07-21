#pragma once
#include "pre.h"

#include <unordered_map>

#include "GLevel.h"
#include "GObject.h"

namespace Lumin
{
	// World manages levels
	class ENGINE_API GWorld : public GObject
	{
	public:
		GWorld();
		void Tick(float deltaTime);
		GLevel* CreateEmptyLevel();
		GLevel* GetLevel(uint32_t levelId);
		GLevel* GetCurrentLevel();
		std::vector<LightInfo> GetCurrentLevelLightsInfo();
		
	private:
		uint32_t m_currentLevel;
		std::unordered_map<uint32_t, GLevel*> m_levels;
	};
}

