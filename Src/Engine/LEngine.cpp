#include "LEngine.h"

#include "LLog.h"
#include "LGameInstanceBase.h"
#include "LViewport.h"
#include "Input/LInputManager.h"
#include "Graphics/LGraphicsCore.h"
#include "Render/LRenderQueue.h"

namespace Lumin
{
	struct LEngine::Impl
	{
		std::unique_ptr<LGameInstanceBase> m_gameInstance;
		std::chrono::steady_clock::time_point m_lastFrameTime;
		LViewport* m_viewport = nullptr;
		LInputManager m_inputManager;
		LGraphicsCore m_graphicsCore;
		LRenderQueue m_renderQueue;
	};

	LEngine& LEngine::GetInstance()
	{
		static LEngine engine;
		return engine;
	}

	LEngine::~LEngine()
	{
		
	}

	bool LEngine::Init(const LEngineConfig& config)
	{
		CHECK_PTR_RETURN_VALUE(m_impl->m_gameInstance, false, "GameInstance is nullptr");
		LViewportConfig viewportConfig{ config.width, config.height, this };
		m_impl->m_viewport = new LViewport(viewportConfig);//手动管理
		CHECK_PTR_RETURN_VALUE(m_impl->m_viewport, false, "Viewport is nullptr");
		return m_impl->m_gameInstance->Init();
	}

	void LEngine::Run()
	{
		CHECK_PTR_RETURN(m_impl->m_gameInstance, "GameInstance is nullptr");
		CHECK_PTR_RETURN(m_impl->m_viewport, "Viewport is nullptr");
		m_impl->m_lastFrameTime = std::chrono::high_resolution_clock::now();
		qDebug() << "Engine Run Thread";
		while(!m_impl->m_viewport->ViewportShouldClose() && !m_impl->m_gameInstance->IsNeedToBeClosed())
		{
			auto nowTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(nowTime - m_impl->m_lastFrameTime).count();
			m_impl->m_lastFrameTime = nowTime;

			m_impl->m_gameInstance->Tick(deltaTime);
			m_impl->m_inputManager.SetMouseOldPos(m_impl->m_inputManager.GetMouseNewPos());
		}
	}

	void LEngine::Destroy()
	{
		CHECK_PTR_RETURN(m_impl->m_gameInstance, "GameInstance is nullptr");

		m_impl->m_gameInstance->Destroy();
		m_impl->m_gameInstance.reset();
		delete m_impl->m_viewport;
		m_impl->m_viewport = nullptr;
	}

	void LEngine::SetGameInstance(LGameInstanceBase* gameInstance)
	{
		CHECK_PTR_RETURN(gameInstance, "GameInstance is nullptr");

		m_impl->m_gameInstance.reset(gameInstance);
	}

	LGameInstanceBase* LEngine::GetGameInstance() const
	{
		return m_impl->m_gameInstance.get();
	}

	LInputManager& LEngine::GetInputManager()
	{
		return m_impl->m_inputManager;
	}

	LGraphicsCore& LEngine::GetGraphicsCore()
	{
		return m_impl->m_graphicsCore;
	}
	LRenderQueue& LEngine::GetRenderQueue()
	{
		return m_impl->m_renderQueue;
	}

	LEngine::LEngine(): m_impl(std::make_unique<Impl>())
	{

	}
}

