#include "LViewport.h"

#include "LEngine.h"
#include "QKeyEvent"
#include "LLog.h"
#include "OpenGLApi/LOpenGLFunctionsManager.h"

namespace Lumin
{

	LViewport::LViewport(const LViewportConfig& config, QWidget* parent)
		: QOpenGLWidget(parent)
	{
		CHECK_PTR_RETURN(config.engine, "config.engine is null");
		m_engine = config.engine;
		if (m_canShow == true)
		{
			resize(config.width, config.height);  // 默认大小
			this->show();
		}
	}

	LViewport::~LViewport()
	{
		
	}

	bool LViewport::ViewportShouldClose() const
	{
		return m_canShow == false;
	}

	void LViewport::initializeGL()
	{
		LOpenGLFunctionsManager::GetInstance().Initialize();
		makeCurrent();
	}

	void LViewport::resizeGL(int w, int h)
	{

	}

	void LViewport::paintGL()
	{

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
}

