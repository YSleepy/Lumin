#pragma once
#include <mutex>

#include "LMeshSceneComponent.h"
#include "Graphics/LGraphicsCore.h"

namespace Lumin
{
	struct RenderObj
	{
		LMeshSceneComponent renderSceneComponent;
	};

	class LRenderQueue
	{
	public:
		void Submit(const RenderObj& renderable);
		void Draw(LGraphicsCore& graphicsCore);
	private:
		std::vector<RenderObj> m_renderQueue;
		std::mutex m_mutex;
	};
}


