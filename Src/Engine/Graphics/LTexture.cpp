#include "LTexture.h"

#include <QImage>

#include "LEngine.h"
#include "FileSystem/LFileSystem.h"
#include "OpenGLApi/LOpenGLFunctionsManager.h"

namespace Lumin
{
	LTexture::LTexture(int width, int height, int channels, const void* data)
	{
		L_GL->glGenTextures(1, &m_textureID);
		L_GL->glBindTexture(GL_TEXTURE_2D, m_textureID);

		L_GL->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		L_GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
			width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		L_GL->glGenerateMipmap(GL_TEXTURE_2D);
		// Set texture wrapping to GL_REPEAT (default wrapping method)
		L_GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		L_GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering options
		L_GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		L_GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	LTexture::~LTexture()
	{
		if (m_textureID > 0)
		{
			L_GL->glDeleteTextures(1, &m_textureID);
		}
	}

	std::shared_ptr<LTexture> LTexture::LoadTextureRGBA8(const char* path)
	{
		auto texturePath = Lumin::LEngine::GetInstance().GetFileSystem().GetEngineAssetsPath() + path;
		QString texturePathStr(texturePath.c_str());
		std::unique_ptr<QImage> sourceImage = std::make_unique<QImage>(texturePathStr);
		QImage image = sourceImage->convertToFormat(QImage::Format_RGBA8888);
		image = image.mirrored(false, true);
		auto texture = std::make_shared<Lumin::LTexture>(image.size().width(), image.size().height(), 3, image.bits());
		return texture;
	}

	GLuint LTexture::GetTextureID() const
	{
		return m_textureID;
	}
}

