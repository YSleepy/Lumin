#pragma once
#include <memory>
#include <chrono>

namespace Lumin
{
	class LGameInstanceBase;
	class LEngine
	{
	public:
		bool Init();
		void Run();
		void Destroy();

		void SetGameInstance(LGameInstanceBase* gameInstance);
		LGameInstanceBase* GetGameInstance() const;
	private:
		std::unique_ptr<LGameInstanceBase> m_gameInstance;
		std::chrono::steady_clock::time_point m_lastFrameTime;
	};
}


