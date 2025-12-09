#pragma once
#include "GComponent.h"

#include "Render/LMaterial.h"
#include "Render/LMesh.h"

namespace Lumin
{
	class GMeshSceneComponent : public GComponent
	{
	public:
		GMeshSceneComponent(const std::shared_ptr<LMesh>& mesh, const std::shared_ptr<LMaterial>& material, const std::string& name);
		void Tick(float deltaTime) override;
		std::shared_ptr<LMesh> m_mesh;
		std::shared_ptr<LMaterial> m_material;
	};

}

