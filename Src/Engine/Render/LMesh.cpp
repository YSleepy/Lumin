#include "LMesh.h"

#include "LEngine.h"
#include "Graphics/LGraphicsCore.h"
#include "OpenGLApi/LOpenGLFunctionsManager.h"

namespace Lumin
{
	LMesh::LMesh(const LVertexLayout& layout, const std::vector<float>& vertices)
	{
		m_layout = layout;
		LGraphicsCore& graphicsCore = LEngine::GetInstance().GetGraphicsCore();
		m_vbo = graphicsCore.CreateVertexBufferObject(vertices);

		L_GL->glGenVertexArrays(1, &m_vao);
		L_GL->glBindVertexArray(m_vao);

		L_GL->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		for (LVertexElement& it : m_layout.elements)
		{
			L_GL->glVertexAttribPointer(it.index, it.size, it.type, GL_FALSE, m_layout.stride, (void*)it.offset);
			L_GL->glEnableVertexAttribArray(it.index);
		}

		L_GL->glBindVertexArray(0);
		L_GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_vertexCount = vertices.size() * sizeof(float) / m_layout.stride;
		m_indexCount = 0;
		qDebug() << "LMesh::LMesh(): this_ptr: " << this;
	}

	LMesh::LMesh(const LVertexLayout& layout, const std::vector<float>& vertices, const std::vector<uint32_t>& indices)
	{
		m_layout = layout;
		LGraphicsCore& graphicsCore = LEngine::GetInstance().GetGraphicsCore();
		m_vbo = graphicsCore.CreateVertexBufferObject(vertices);
		m_ebo = graphicsCore.CreateIndexBufferObject(indices);

		L_GL->glGenVertexArrays(1, &m_vao);
		L_GL->glBindVertexArray(m_vao);

		L_GL->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		L_GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

		for (LVertexElement& it : m_layout.elements)
		{
			L_GL->glVertexAttribPointer(it.index, it.size, it.type, GL_FALSE, m_layout.stride, (void*)it.offset);
			L_GL->glEnableVertexAttribArray(it.index);
		}

		L_GL->glBindVertexArray(0);
		L_GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
		L_GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		m_vertexCount = vertices.size() * sizeof(float) / m_layout.stride;
		m_indexCount = indices.size();
	}

	LMesh::~LMesh()
	{
		qDebug() << "LMesh::~LMesh(): this_ptr: " << this;
	}

	void LMesh::Bind()
	{
		L_GL->glBindVertexArray(m_vao);
		L_GL->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		L_GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		L_GL->CheckOpenGLError();
	}

	void LMesh::Draw()
	{
		if (m_indexCount > 0)
		{
			//L_GL->CheckOpenGLContext();
			//L_GL->CheckThreadContextAssociation();
			//L_GL->PrintCurrentState();
			L_GL->glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

			L_GL->CheckOpenGLError();
		}
		else
		{
			L_GL->glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
		}
	}
}
