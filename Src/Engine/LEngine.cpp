#include "LEngine.h"

#include "LLog.h"
#include "LGameInstanceBase.h"

namespace Lumin
{
	bool LEngine::Init()
	{
		CHECK_PTR_RETURN_VALUE(m_gameInstance, false, "GameInstance is nullptr");
		return m_gameInstance->Init();
	}

	void LEngine::Run()
	{
		CHECK_PTR_RETURN(m_gameInstance, "GameInstance is nullptr");
		m_lastFrameTime = std::chrono::high_resolution_clock::now();
		while(!m_gameInstance->IsNeedToBeClosed())
		{
			auto nowTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(nowTime - m_lastFrameTime).count();
			m_lastFrameTime = nowTime;

			m_gameInstance->Tick(deltaTime);
		}
	}

	void LEngine::Destroy()
	{
		CHECK_PTR_RETURN(m_gameInstance, "GameInstance is nullptr");

		m_gameInstance->Destroy();
		m_gameInstance.reset();
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
}

