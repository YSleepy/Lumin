#include "LRenderQueue.h"

namespace Lumin
{
	void LRenderQueue::Submit(RenderObj renderable)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_renderQueue.push_back(renderable);
	}

	void LRenderQueue::Draw(LGraphicsCore& graphicsCore)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		qDebug() << "Drawing " << m_renderQueue.size() << " objects";

		for (auto& renderable : m_renderQueue)
		{
			qDebug() << "mesh ptr: " << renderable.renderSceneComponent->m_mesh;
			graphicsCore.BindMesh(renderable.renderSceneComponent->m_mesh);
			graphicsCore.BindMaterial(renderable.renderSceneComponent->m_material);
			graphicsCore.DrawMesh(renderable.renderSceneComponent->m_mesh);
		}
		m_renderQueue.clear();
	}
}

