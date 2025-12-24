#pragma once
#include "pre.h"

#include <memory>
#include <string>

namespace Lumin
{
	struct ENGINE_API LEngineConfig
	{
		int width;
		int height;
		std::string gameRootPath;
	};

	class LGameInstanceBase;
	class LInputManager;
	class LGraphicsCore;
	class LRenderQueue;
	class LFileSystem;

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
		LFileSystem& GetFileSystem();

	private:
		LEngine();
		LEngine& operator=(const LEngine&) = delete;
		LEngine& operator=(LEngine&&) = delete;
	private:
		// Pimpl (Pointer to implementation)
		struct Impl;
		std::unique_ptr<Impl> m_impl;
	};
}


