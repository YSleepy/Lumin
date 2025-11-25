#pragma once

#include <QOpenGLFunctions_3_3_Core>

class LOpenGLFunctionsManager : public QOpenGLFunctions_3_3_Core
{
	Q_DISABLE_COPY(LOpenGLFunctionsManager)

public:
	static LOpenGLFunctionsManager& GetInstance() {
		static LOpenGLFunctionsManager instance;
		return instance;
	}

	bool Initialize() {
		if (!m_initialized) {
			m_initialized = initializeOpenGLFunctions();
		}
		return m_initialized;
	}

	bool IsInitialized() const { return m_initialized; }

	void CheckOpenGLError()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			qDebug() << "OpenGL error after initialization:" << error;
		}
	}

private:
	LOpenGLFunctionsManager() = default;
	bool m_initialized = false;
};

// 便捷宏
#define L_GL LOpenGLFunctionsManager::GetInstance()
