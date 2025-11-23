#pragma once
#include <memory>
#include <chrono>

#include "LViewport.h"
#include "Input/LInputManager.h"
#include "Graphics/LGraphicsCore.h"

namespace Lumin
{
	struct LEngineConfig
	{
		LViewportConfig viewportConfig;
	};

	class LGameInstanceBase;
	class LEngine
	{
	public:
		static LEngine& GetInstance();
		bool Init(const LEngineConfig& config);
		void Run();
		void Destroy();

		void SetGameInstance(LGameInstanceBase* gameInstance);
		LGameInstanceBase* GetGameInstance() const;
		LInputManager& GetInputManager();
		LGraphicsCore& GetGraphicsCore();
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
	};
}


