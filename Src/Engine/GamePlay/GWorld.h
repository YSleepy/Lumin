#pragma once
#include <unordered_map>

#include "GLevel.h"
#include "GObject.h"

namespace Lumin
{
	// World manages levels
	class GWorld : public GObject
	{
	public:
		GWorld();
		void Tick(float deltaTime);
		std::unique_ptr<GLevel> CreateEmptyLevel();
		GLevel* GetLevel(uint32_t levelId);
		GLevel* GetCurrentLevel();
		
	private:
		uint32_t m_currentLevel;
		std::unordered_map<uint32_t, std::unique_ptr<GLevel>> m_levels;
	};
}

