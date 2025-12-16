#pragma once
#include "pre.h"

#include <memory>
#include <chrono>

#include "LGameInstanceBase.h"
#include "LViewport.h"
#include "Input/LInputManager.h"
#include "Graphics/LGraphicsCore.h"
#include "Render/LRenderQueue.h"

namespace Lumin
{
	struct ENGINE_API LEngineConfig
	{
		LViewportConfig viewportConfig;
	};

	class ENGINE_API LEngine
	{
	public:
		static LEngine& GetInstance();
		~LEngine();
		bool Init(const LEngineConfig& config);
		void Run();
		void Destroy();

		void SetGameInstance(LGameInstanceBase* gameInstance);
		LGameInstanceBase* GetGameInstance() const;
		LInputManager& GetInputManager();
		LGraphicsCore& GetGraphicsCore();
		LRenderQueue& GetRenderQueue();
	private:
		LEngine() = default;
		LEngine& operator=(const LEngine&) = delete;
		LEngine& operator=(LEngine&&) = delete;
	private:
		std::unique_ptr<LGameInstanceBase> m_gameInstance;
		std::chrono::steady_clock::time_point m_lastFrameTime;
		LViewport* m_viewport = nullptr;
		LInputManager m_inputManager;
		LGraphicsCore m_graphicsCore;
		LRenderQueue m_renderQueue;
	};
}


