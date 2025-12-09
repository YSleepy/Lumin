#pragma once
#include "GamePlay/GActor.h"
#include "Render/LMaterial.h"
#include "Render/LMesh.h"

class MyActor : public Lumin::GActor
{
public:
	MyActor();
	void Tick(float deltaTime) override;
};

