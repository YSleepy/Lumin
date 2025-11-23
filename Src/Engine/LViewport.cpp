#include "LViewport.h"

#include "LEngine.h"
#include "QKeyEvent"
#include "LLog.h"

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
			makeCurrent();
			this->show();
		}
	}

	LViewport::~LViewport()
	{
		doneCurrent();
	}

	bool LViewport::ViewportShouldClose() const
	{
		return m_canShow == false;
	}

	void LViewport::initializeGL()
	{

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

