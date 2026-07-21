#include "LOpenGLFunctionsManager.h"

#include <QSurface>
#include <QThread>

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
		qDebug() << "Initializing OpenGL functions";
		if (!m_initialized) {
			m_initialized = initializeOpenGLFunctions();
		}
		return m_initialized;
	}

	void LOpenGLFunctionsManager::CheckOpenGLError()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			qDebug() << "CheckOpenGLError:" << error;
		}
	}

	void LOpenGLFunctionsManager::CheckOpenGLContext()
	{
		qDebug() << "\n=== OpenGL Context State Check ===";

		QOpenGLContext* currentContext = QOpenGLContext::currentContext();
		if (!currentContext) {
			qDebug() << "Error: OpenGLContext is nullptr!";
			return;
		}
		qDebug() << "OpenGL Context is ok";

		if (!currentContext->isValid()) {
			qDebug() << "Error: OpenGL Context is invalid!";
			return;
		}
		qDebug() << "OpenGL Context is valid";

		QSurfaceFormat format = currentContext->format();
		qDebug() << "OpenGL Version:" << format.majorVersion() << "." << format.minorVersion();
		qDebug() << "Profile:" << (format.profile() == QSurfaceFormat::CoreProfile ? "Core" :
			(format.profile() == QSurfaceFormat::CompatibilityProfile ? "Compatibility" : "None"));

		if (!currentContext->functions()) {
			qDebug() << "Error: OpenGL functions is unavailable!";
			return;
		}
		qDebug() << "OpenGL functions is ok";

		GLint maxTextureSize;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
		CheckOpenGLError();
		qDebug() << "GL_MAX_TEXTURE_SIZE:" << maxTextureSize;

		GLint maxVertexAttribs;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
		CheckOpenGLError();
		qDebug() << "GL_MAX_VERTEX_ATTRIBS:" << maxVertexAttribs;

		qDebug() << "Context check completed, fully functional!";
	}

	void LOpenGLFunctionsManager::CheckThreadContextAssociation()
	{
		qDebug() << "\n=== Thread and context correlation check ===";

		QOpenGLContext* context = QOpenGLContext::currentContext();
		if (!context) {
			qDebug() << "The current thread does not have OpenGL context";
			return;
		}

		qDebug() << "current thread ID:" << QThread::currentThreadId();
		qDebug() << "Context thread association:" << (context->thread() == QThread::currentThread() ? "match" : "mismatch");

		QSurface* surface = context->surface();
		if (surface) {
			qDebug() << "Surface size:" << surface->size().width() << "x" << surface->size().height();
		}
		else {
			qDebug() << "Surface without context correlation!";
		}
	}

	void LOpenGLFunctionsManager::PrintCurrentState()
	{
		if (!QOpenGLContext::currentContext() || !QOpenGLContext::currentContext()->isValid()) {
			qDebug() << "Unable to perform rendering test: Invalid context";
			return;
		}
		qDebug() << "\n=== Frame buffer status ===";

		GLint currentFBO;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFBO);
		CheckOpenGLError();
		qDebug() << "Currently bound FBO ID:" << currentFBO;

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		CheckOpenGLError();
		qDebug() << "Viewport position/size (x, y, w, h):" << viewport[0] << "," << viewport[1] << "," << viewport[2] << "," << viewport[3];

		GLint colorBits[4];
		glGetIntegerv(GL_RED_BITS, &colorBits[0]);
		CheckOpenGLError();
		glGetIntegerv(GL_GREEN_BITS, &colorBits[1]);
		CheckOpenGLError();
		glGetIntegerv(GL_BLUE_BITS, &colorBits[2]);
		CheckOpenGLError();
		glGetIntegerv(GL_ALPHA_BITS, &colorBits[3]);
		CheckOpenGLError();
		qDebug() << "Color Buffer Bit Depth (RGBA):" << colorBits[0] << "/" << colorBits[1] << "/" << colorBits[2] << "/" << colorBits[3];

		GLint depthBits;
		glGetIntegerv(GL_DEPTH_BITS, &depthBits);
		CheckOpenGLError();
		qDebug() << "Depth buffer bit depth:" << depthBits;

		qDebug() << "\n=== Shaders and Vertex Object States ===";

		GLint currentProgram;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
		CheckOpenGLError();
		qDebug() << "The currently activated shader program ID:" << currentProgram;

		GLint currentVAO;
		glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);
		CheckOpenGLError();
		qDebug() << "Currently bound VAO ID:" << currentVAO;

		GLint currentVBO;
		glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentVBO);
		CheckOpenGLError();
		qDebug() << "Currently bound VBO ID（ARRAY_BUFFER）:" << currentVBO;
	}
}
