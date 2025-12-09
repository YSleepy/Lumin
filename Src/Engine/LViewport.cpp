#include "LViewport.h"

#include <QTimer>

#include "LEngine.h"
#include "LGameInstanceBase.h"
#include "QKeyEvent"
#include "LLog.h"
#include "GamePlay/Component/GCameraComponent.h"
#include "OpenGLApi/LOpenGLFunctionsManager.h"

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
			timer->start(16);
			resize(config.width, config.height);
			this->show();
		}
	}

	LViewport::~LViewport()
	{
		LOpenGLFunctionsManager::DestroyInstance();
		qDebug() << "LViewport::~LViewport()";
	}

	void LViewport::initializeGL()
	{
		LOpenGLFunctionsManager::GetInstance()->Initialize();
		L_GL->glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		L_GL->glEnable(GL_DEPTH_TEST);
		qDebug() << "OpenGL initialized successfully";
		qDebug() << "OpenGL Version:" << (const char*)L_GL->glGetString(GL_VERSION);
		qDebug() << "GLSL Version:" << (const char*)L_GL->glGetString(GL_SHADING_LANGUAGE_VERSION);
	}

	void LViewport::resizeGL(int w, int h)
	{
		L_GL->glViewport(0, 0, w, h);
		qDebug() << "Viewport resized to:" << w << "x" << h;
	}

	void LViewport::paintGL()
	{
		L_GL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		auto defaultActor = m_engine->GetGameInstance()->GetDefaultActor();
		auto camera = defaultActor->GetComponentByName<GCameraComponent>();
		CHECK_CONDITION_RETURN(camera, "camera is null");
		CameraInfo cameraInfo{
			camera->GetViewMatrix(),
			camera->GetProjectionMatrix()
		};
		
		m_engine->GetRenderQueue().Draw(m_engine->GetGraphicsCore(), cameraInfo);
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
		m_canShow = false;
	}

	bool LViewport::ViewportShouldClose() const
	{
		return m_canShow == false;
	}
}

