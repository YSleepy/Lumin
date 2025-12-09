#include "GMeshSceneComponent.h"

#include "LEngine.h"
#include "Render/LRenderQueue.h"
#include "GamePlay/GActor.h"

namespace Lumin
{
	GMeshSceneComponent::GMeshSceneComponent(
		const std::shared_ptr<LMesh>& mesh,
		const std::shared_ptr<LMaterial>& material,
		const std::string& name
	): GComponent(name)
	{
		m_mesh = mesh;
		m_material = material;
	}

	void GMeshSceneComponent::Tick(float deltaTime)
	{
		Lumin::RenderCmd ro;
		ro.m_material = m_material.get();
		ro.m_mesh = m_mesh.get();
		ro.m_modelMatrix = GetOwner()->GetWorldTransform();
		auto& renderQueue = Lumin::LEngine::GetInstance().GetRenderQueue();
		renderQueue.Submit(ro);
	}
}
