#pragma once

#include "LGameInstanceBase.h"
#include "Render/LMaterial.h"
#include "Render/LMesh.h"

class EGameInstance : public Lumin::LGameInstanceBase
{
public:
	bool Init() override;
	void Tick(float deltaTime) override;
	void Destroy() override;
private:
	Lumin::LMaterial m_firstMaterial;
	std::unique_ptr<Lumin::LMesh> m_firstMesh;
	float m_offsetX = 0.0f;
	float m_offsetY = 0.0f;
};
