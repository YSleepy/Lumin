#pragma once
#include "pre.h"

#include "Graphics/LVertexLayout.h"

namespace Lumin
{
	class ENGINE_API LMesh
	{
		Q_DISABLE_COPY(LMesh)
	public:
		static std::shared_ptr<LMesh> LoadMesh(const char* path);
		LMesh(const LVertexLayout& layout, const std::vector<float>& vertices);
		LMesh(const LVertexLayout& layout, const std::vector<float>& vertices, const std::vector<uint32_t>& indices);
		~LMesh();
		const std::vector<float>& GetVertices() const;
		const std::vector<uint32_t>& GetIndices() const;
		void Bind();
		void Draw();
	private:
		std::vector<float> m_vertices {};
		std::vector<uint32_t> m_indices {};
		GLuint m_vao = 0;
		GLuint m_vbo = 0;
		GLuint m_ebo = 0;
		LVertexLayout m_layout;

		size_t m_vertexCount = 0;
		size_t m_indexCount = 0;
	};

}

