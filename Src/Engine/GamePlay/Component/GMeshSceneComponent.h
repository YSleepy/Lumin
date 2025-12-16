#pragma once
#include "pre.h"

#include <memory>

#include "GComponent.h"
#include "Render/LMaterial.h"
#include "Render/LMesh.h"

namespace Lumin
{
	class ENGINE_API GMeshSceneComponent : public GComponent
	{
	public:
		GMeshSceneComponent(const std::shared_ptr<LMesh>& mesh, const std::shared_ptr<LMaterial>& material, const std::string& name);
		~GMeshSceneComponent() override;
		void Tick(float deltaTime) override;
	private:
		std::shared_ptr<LMesh> m_mesh;
		std::shared_ptr<LMaterial> m_material;
	};
}

