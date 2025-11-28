#include "LOpenGLFunctionsManager.h"

namespace Lumin
{
	LOpenGLFunctionsManager* LOpenGLFunctionsManager::s_instance = nullptr;

	LOpenGLFunctionsManager* LOpenGLFunctionsManager::GetInstance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new LOpenGLFunctionsManager();
		}
		return s_instance;
	}

	void LOpenGLFunctionsManager::DestroyInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}

	bool LOpenGLFunctionsManager::Initialize()
	{
		if (!m_initialized) {
			m_initialized = initializeOpenGLFunctions();
		}
		return m_initialized;
	}

	void LOpenGLFunctionsManager::CheckOpenGLError()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			qDebug() << "OpenGL error after initialization:" << error;
		}
	}
}
