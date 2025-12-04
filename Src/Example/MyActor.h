#pragma once
#include "GamePlay/GActor.h"
#include "Render/LMaterial.h"
#include "Render/LMesh.h"

class MyActor : public Lumin::GActor
{
public:
	MyActor();
	void Tick(float deltaTime) override;
private:
	Lumin::LMaterial m_firstMaterial;
	std::unique_ptr<Lumin::LMesh> m_firstMesh;
	float m_offsetX = 0.0f;
	float m_offsetY = 0.0f;
};

