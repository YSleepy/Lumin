#pragma once
#include <mutex>

#include "Graphics/LGraphicsCore.h"

namespace Lumin
{
	const std::string MODEL_MATRIX = "modelMatrix";
	const std::string VIEW_MATRIX = "viewMatrix";
	struct RenderCmd
	{
		LMesh* m_mesh;
		LMaterial* m_material;
		QMatrix4x4 m_modelMatrix;
	};

	struct CameraInfo
	{
		QMatrix4x4 ViewMatrix;
		QMatrix4x4 ProjectionMatrix;
	};

	class LRenderQueue
	{
	public:
		void Submit(const RenderCmd& renderable);
		void Draw(LGraphicsCore& graphicsCore, const CameraInfo& cameraInfo);

	private:
		std::vector<RenderCmd> m_renderQueue;
		std::mutex m_mutex;
	};
}


