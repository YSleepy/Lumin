#pragma once

#include <QOpenGLFunctions_3_3_Core>

namespace Lumin
{
	class LOpenGLFunctionsManager : public QOpenGLFunctions_3_3_Core
	{
		Q_DISABLE_COPY(LOpenGLFunctionsManager)

	public:
		static LOpenGLFunctionsManager* GetInstance();
		// 也可将其私有化，将LViewport作为友元
		static void DestroyInstance();
		bool Initialize();
		bool IsInitialized() const { return m_initialized; }
		void CheckOpenGLError();

	private:
		LOpenGLFunctionsManager() = default;
		~LOpenGLFunctionsManager() = default;
		static LOpenGLFunctionsManager* s_instance;
		bool m_initialized = false;
	};

	// 便捷宏
#define L_GL LOpenGLFunctionsManager::GetInstance()

}

