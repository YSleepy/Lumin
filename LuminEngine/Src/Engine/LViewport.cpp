#include "LViewport.h"

#include <QTimer>

#include "LEngine.h"
#include "LGameInstanceBase.h"
#include "QKeyEvent"
#include "LLog.h"
#include "GamePlay/Component/GCameraComponent.h"
#include "OpenGLApi/LOpenGLFunctionsManager.h"
#include "Render/LRenderQueue.h"
#include "Input/LInputManager.h"

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
			timer->start(1);
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
		L_GL->glEnable(GL_DEPTH_TEST); // enable depth testing

		L_GL->glEnable(GL_BLEND); // enable blending
		L_GL->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // set blending function

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
		CHECK_CONDITION_RETURN(defaultActor, "defaultActor is null");
		auto camera = defaultActor->GetComponent<GCameraComponent>();
		CHECK_CONDITION_RETURN(camera, "camera is null");
		float aspectRatio = static_cast<float>(width()) / static_cast<float>(height());
		CameraInfo cameraInfo{
			camera->GetViewMatrix(),
			camera->GetProjectionMatrix(aspectRatio),
		};

		auto lightsInfos = m_engine->GetGameInstance()->GetWorld()->GetCurrentLevelLightsInfo();
		
		m_engine->GetRenderQueue().Draw(m_engine->GetGraphicsCore(), cameraInfo, lightsInfos);
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

	void LViewport::mouseMoveEvent(QMouseEvent* event)
	{
		qDebug() << "mouseMoveEvent" << event->position();
		QVector2D pos (event->position().x(), event->position().y());
		m_engine->GetInputManager().SetMouseOldPos(m_engine->GetInputManager().GetMouseNewPos());
		m_engine->GetInputManager().SetMouseNewPos(pos);
	}

	void LViewport::mousePressEvent(QMouseEvent* event)
	{
		qDebug() << "mousePressEvent" << event->button();
		m_engine->GetInputManager().SetButton(event->button(), true);
		QVector2D pos(event->position().x(), event->position().y());
		m_engine->GetInputManager().SetMouseOldPos(pos);
		m_engine->GetInputManager().SetMouseNewPos(pos);
	}

	void LViewport::mouseReleaseEvent(QMouseEvent* event)
	{
		qDebug() << "mouseReleaseEvent" << event->button();
		m_engine->GetInputManager().SetButton(event->button(), false);
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

