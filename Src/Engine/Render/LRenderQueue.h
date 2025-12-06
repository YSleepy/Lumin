#pragma once
#include <mutex>

#include "LMeshSceneComponent.h"
#include "Graphics/LGraphicsCore.h"

namespace Lumin
{
	const std::string MODEL_MATRIX = "modelMatrix";
	struct RenderCmd
	{
		LMeshSceneComponent renderSceneComponent;
	};

	class LRenderQueue
	{
	public:
		void Submit(const RenderCmd& renderable);
		void Draw(LGraphicsCore& graphicsCore);
	private:
		std::vector<RenderCmd> m_renderQueue;
		std::mutex m_mutex;
	};
}


