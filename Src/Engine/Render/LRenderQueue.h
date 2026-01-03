#pragma once
#include <mutex>

#include "pre.h"
#include "Common.h"
#include "Graphics/LGraphicsCore.h"

namespace Lumin
{
	const std::string MODEL_MATRIX = "modelMatrix";
	const std::string VIEW_MATRIX = "viewMatrix";
	const std::string PROJECTION_MATRIX = "projectionMatrix";
	const std::string LIGHT_COLOR = "aLight.color";
	const std::string LIGHT_POSITION = "aLight.position";
	struct ENGINE_API RenderCmd
	{
		LMesh* m_mesh;
		LMaterial* m_material;
		QMatrix4x4 m_modelMatrix;
	};

	class ENGINE_API LRenderQueue
	{
	public:
		void Submit(const RenderCmd& renderable);
		void Draw(LGraphicsCore& graphicsCore, const CameraInfo& cameraInfo, const std::vector<LightInfo>& lightInfos);

	private:
		std::vector<RenderCmd> m_renderQueue;
		std::mutex m_mutex;
	};
}


