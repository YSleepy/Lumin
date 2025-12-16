#pragma once
#include "Engine/GamePlay/GActor.h"

class MyActor : public Lumin::GActor
{
public:
	MyActor();
	void Tick(float deltaTime) override;
};

