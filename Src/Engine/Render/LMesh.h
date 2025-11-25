#pragma once
#include <QOpenGLFunctions_3_3_Core>

#include "Graphics/LVertexLayout.h"

namespace Lumin
{
	class LMesh
	{
		Q_DISABLE_COPY(LMesh)
	public:
		LMesh(const LVertexLayout& layout, const std::vector<float>& vertices);
		LMesh(const LVertexLayout& layout, const std::vector<float>& vertices, const std::vector<uint32_t>& indices);
		~LMesh();
		void Bind();
		void Draw();
	private:
		GLuint m_vao = 0;
		GLuint m_vbo = 0;
		GLuint m_ebo = 0;
		LVertexLayout m_layout;

		size_t m_vertexCount = 0;
		size_t m_indexCount = 0;
	};

}

