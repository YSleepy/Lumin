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
		initializeOpenGLFunctions();

		makeCurrent();
		qDebug() << "=== OpenGL Context Check ===";
		qDebug() << "Is valid:" << isValid();
		qDebug() << "Format:" << format();

		// 检查函数是否初始化成功
		if (&LOpenGLFunctionsManager::glClearColor == nullptr) {
			qDebug() << "OpenGL functions not properly initialized!";
			return;
		}
		L_GL.glClearColor(1.f, 1.f, 1.f, 1.0f);
		L_GL.glEnable(GL_DEPTH_TEST);
		// 检查是否有GL错误
		GLenum error = L_GL.glGetError();
		if (error != GL_NO_ERROR) {
			qDebug() << "OpenGL error after initialization:" << error;
		}

		qDebug() << "OpenGL initialized successfully";
		qDebug() << "OpenGL version:" << (const char*)L_GL.glGetString(GL_VERSION);
	}

	void LViewport::resizeGL(int w, int h)
	{
		qDebug() << "resizeGL:" << w << "x" << h;
		L_GL.glViewport(0, 0, w, h);
	}

	void checkOpenGLState()
	{
		qDebug() << "=== OpenGL State Check ===";

		// 检查错误状态
		GLenum error = L_GL.glGetError();
		if (error != GL_NO_ERROR) {
			qDebug() << "OpenGL Error:" << (error);
		}

		// 检查视口设置
		GLint viewport[4];
		L_GL.glGetIntegerv(GL_VIEWPORT, viewport);
		qDebug() << "Viewport:" << viewport[0] << viewport[1] << viewport[2] << viewport[3];

		// 检查清除颜色
		GLfloat clearColor[4];
		L_GL.glGetFloatv(GL_COLOR_CLEAR_VALUE, clearColor);
		qDebug() << "Clear color:" << clearColor[0] << clearColor[1] << clearColor[2] << clearColor[3];

		// 检查深度测试
		GLboolean depthTest;
		L_GL.glGetBooleanv(GL_DEPTH_TEST, &depthTest);
		qDebug() << "Depth test enabled:" << depthTest;

		// 检查当前绑定的VAO
		GLint currentVAO;
		L_GL.glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);
		qDebug() << "Current VAO:" << currentVAO;

		// 检查当前绑定的VBO
		GLint currentVBO;
		L_GL.glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentVBO);
		qDebug() << "Current VBO:" << currentVBO;

		// 检查当前绑定的EBO
		GLint currentEBO;
		L_GL.glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentEBO);
		qDebug() << "Current EBO:" << currentEBO;

		// 检查帧缓冲区
		GLint drawFBO, readFBO;
		L_GL.glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFBO);
		L_GL.glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFBO);
		qDebug() << "Draw FBO:" << drawFBO << "Read FBO:" << readFBO;
	}

	void LViewport::paintGL()
	{
		qDebug() << "paintGL";
		L_GL.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLenum error = L_GL.glGetError();
		if (error != GL_NO_ERROR) {
			qDebug() << "OpenGL error before draw:" << error;
		}
		m_engine->GetRenderQueue().Draw(m_engine->GetGraphicsCore());
		checkOpenGLState();// debug
		error = L_GL.glGetError();
		qDebug() << "OpenGL error after draw:" << error;
		if (error != GL_NO_ERROR) {
			qDebug() << "OpenGL error after draw:" << error;
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
}

