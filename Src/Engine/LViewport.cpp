#include "LViewport.h"

#include "LEngine.h"
#include "QKeyEvent"
#include "LLog.h"
#include "OpenGLApi/LOpenGLFunctionsManager.h"
#include <QTimer>

namespace Lumin
{
	LViewport::LViewport(const LViewportConfig& config, QWidget* parent) : QOpenGLWidget(parent)
	{
		CHECK_PTR_RETURN(config.engine, "config.engine is null");
		m_engine = config.engine;
		if (m_canShow == true)
		{
			QTimer* timer = new QTimer(this);
			connect(timer, &QTimer::timeout, this, [this]() {
				update();
				});
			timer->start(16); // 约60fps
			resize(config.width, config.height);  // 默认大小
			this->show();
		}
	}

	void LViewport::initializeGL()
	{
		LOpenGLFunctionsManager::GetInstance().Initialize();
		L_GL.glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		L_GL.glEnable(GL_DEPTH_TEST);
		qDebug() << "OpenGL initialized successfully";
		qDebug() << "OpenGL Version:" << (const char*)L_GL.glGetString(GL_VERSION);
		qDebug() << "GLSL Version:" << (const char*)L_GL.glGetString(GL_SHADING_LANGUAGE_VERSION);
	}

	void LViewport::resizeGL(int w, int h)
	{
		L_GL.glViewport(0, 0, w, h);
		qDebug() << "Viewport resized to:" << w << "x" << h;
	}

	void LViewport::paintGL()
	{
		//m_engine->GetRenderQueue().Draw(m_engine->GetGraphicsCore());
		static int frameCount = 0;
		frameCount++;

		float r = (sin(frameCount * 0.01f) + 1.0f) * 0.5f * 0.3f + 0.2f;
		float g = (cos(frameCount * 0.02f) + 1.0f) * 0.5f * 0.3f + 0.2f;
		float b = (sin(frameCount * 0.03f) + 1.0f) * 0.5f * 0.3f + 0.4f;

		L_GL.glClearColor(r, g, b, 1.0f);

		L_GL.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLenum error = L_GL.glGetError();
		if (error != GL_NO_ERROR) {
			qDebug() << "OpenGL error in frame" << frameCount << ":" << error;
		}

		if (frameCount % 100 == 0) {
			qDebug() << "Frame" << frameCount << "cleared with color:" << r << g << b;
		}
	}

	void LViewport::keyPressEvent(QKeyEvent* event)
	{
		if (!event->isAutoRepeat())
		{
			qDebug() << "keyPressEvent" << event->key();
			m_engine->GetInputManager().SetKeyPressed(event->key(), true);
		}
	}

	void LViewport::keyReleaseEvent(QKeyEvent* event)
	{
		if (!event->isAutoRepeat())
		{
			qDebug() << "keyReleaseEvent" << event->key();
			m_engine->GetInputManager().SetKeyPressed(event->key(), false);
		}
	}

	void LViewport::closeEvent(QCloseEvent* event)
	{
		QOpenGLWidget::closeEvent(event);
		m_canShow = false;
	}

	bool LViewport::ViewportShouldClose() const
	{
		return m_canShow == false;
	}
}

