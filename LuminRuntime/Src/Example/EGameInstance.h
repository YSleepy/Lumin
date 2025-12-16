#pragma once

#include "Engine/LGameInstanceBase.h"

class EGameInstance : public Lumin::LGameInstanceBase
{
public:
	bool Init() override;
	void Tick(float deltaTime) override;
	void Destroy() override;
};
