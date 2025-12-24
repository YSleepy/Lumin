#pragma once
#include "pre.h"
#include <QOpenGLFunctions_3_3_Core>

namespace Lumin
{
	class ENGINE_API LTexture
	{
	public:
		LTexture(int width, int height, int channels, const void* data);
		LTexture(const LTexture&) = delete;
		LTexture& operator=(const LTexture&) = delete;
		~LTexture();

		GLuint GetTextureID() const;
	private:
		GLuint m_textureID = 0;
		int m_width = 0;
		int m_height = 0;
		int m_channels = 0;
	};

}

