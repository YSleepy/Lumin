#pragma once

#include "LGameInstanceBase.h"
#include "GamePlay/GWorld.h"

class EGameInstance : public Lumin::LGameInstanceBase
{
public:
	bool Init() override;
	void Tick(float deltaTime) override;
	void Destroy() override;
	Lumin::GLevel* GetCurrentLevel();
	Lumin::GWorld* GetWorld();
private:
	Lumin::GWorld m_world;
	

};
