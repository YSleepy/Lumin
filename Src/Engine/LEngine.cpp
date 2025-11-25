#include "LEngine.h"

#include "LLog.h"
#include "LGameInstanceBase.h"
#include "LViewport.h"

namespace Lumin
{
	LEngine& LEngine::GetInstance()
	{
		static LEngine engine;
		return engine;
	}

	bool LEngine::Init(const LEngineConfig& config)
	{
		CHECK_PTR_RETURN_VALUE(m_gameInstance, false, "GameInstance is nullptr");
		LViewportConfig viewportConfig = config.viewportConfig;
		viewportConfig.engine = this;
		m_viewport = new LViewport(viewportConfig);//手动管理
		CHECK_PTR_RETURN_VALUE(m_viewport, false, "Viewport is nullptr");
		return m_gameInstance->Init();
	}

	void LEngine::Run()
	{
		CHECK_PTR_RETURN(m_gameInstance, "GameInstance is nullptr");
		CHECK_PTR_RETURN(m_viewport, "Viewport is nullptr");
		m_lastFrameTime = std::chrono::high_resolution_clock::now();
		while(!m_viewport->ViewportShouldClose() && !m_gameInstance->IsNeedToBeClosed())
		{
			auto nowTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(nowTime - m_lastFrameTime).count();
			m_lastFrameTime = nowTime;

			m_gameInstance->Tick(deltaTime);

			//m_renderQueue.Draw(m_graphicsCore);
			//m_viewport->update();
		}
	}

	void LEngine::Destroy()
	{
		CHECK_PTR_RETURN(m_gameInstance, "GameInstance is nullptr");

		m_gameInstance->Destroy();
		m_gameInstance.reset();
		delete m_viewport;
		m_viewport = nullptr;
	}

	void LEngine::SetGameInstance(LGameInstanceBase* gameInstance)
	{
		CHECK_PTR_RETURN(gameInstance, "GameInstance is nullptr");

		m_gameInstance.reset(gameInstance);
	}

	LGameInstanceBase* LEngine::GetGameInstance() const
	{
		return m_gameInstance.get();
	}

	LInputManager& LEngine::GetInputManager()
	{
		return m_inputManager;
	}

	LGraphicsCore& LEngine::GetGraphicsCore()
	{
		return m_graphicsCore;
	}
	LRenderQueue& LEngine::GetRenderQueue()
	{
		return m_renderQueue;
	}
}

