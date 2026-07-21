#pragma once

#include <vector>
#include <QOpenGLFunctions_3_3_Core>
#include "pre.h"

namespace Lumin
{
	struct ENGINE_API LVertexElement
	{
		GLuint index;// vertex element index, eg. layout(location = 0) in vec3 position; index = 0
		GLint size;// vertex element size, eg. vec3 position; size = 3
		GLenum type;// vertex element type, eg. vec3 position; type = GL_FLOAT
		uint32_t offset;// vertex element offset
	};

	struct ENGINE_API LVertexLayout
	{
		std::vector<LVertexElement> elements;// vertex elements, eg. position, normal, color, uv
		uint32_t stride = 0;// vertex layout stride
	};
}
