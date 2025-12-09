#include "LRenderQueue.h"

namespace Lumin
{
	void LRenderQueue::Submit(const RenderCmd &renderable)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_renderQueue.push_back(renderable);
	}

	void LRenderQueue::Draw(LGraphicsCore& graphicsCore, const CameraInfo& cameraInfo)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_renderQueue.size() > 0)
		{
			qDebug() << "Drawing " << m_renderQueue.size() << " objects";
		}

		for (auto& renderable : m_renderQueue)
		{
			graphicsCore.BindMesh(renderable.m_mesh);
			renderable.m_material->Set4MatrixParam(MODEL_MATRIX, renderable.m_modelMatrix);
			//renderable.m_material->Set4MatrixParam(VIEW_MATRIX, m_viewMatrix);
			graphicsCore.BindMaterial(renderable.m_material);
			graphicsCore.DrawMesh(renderable.m_mesh);
		}
		m_renderQueue.clear();
	}
}

