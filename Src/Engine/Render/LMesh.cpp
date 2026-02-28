#include "LMesh.h"

#include "LEngine.h"
#include "tiny_gltf.h"
#include "FileSystem/LFileSystem.h"
#include "Graphics/LGraphicsCore.h"
#include "OpenGLApi/LOpenGLFunctionsManager.h"

namespace Lumin
{
	// TODO: Temporarily load mesh, This function is too time-consuming
	std::shared_ptr<LMesh> LMesh::LoadMesh(const char* path)
	{
		std::string rPath = LFileSystem::GetEngineAssetsPath() + path;
		tinygltf::Model model;
		tinygltf::TinyGLTF loader;
		std::string err;
		std::string warn;
		bool ok = loader.LoadASCIIFromFile(&model, &err, &warn, rPath);
		if (!warn.empty() || !err.empty())
		{
			qDebug() << "LoadMesh: " << warn << err;
		}
		std::shared_ptr<LMesh> ret = nullptr;
		tinygltf::Accessor accs[3] = {};
		auto& mesh = model.meshes[2];
		auto& primitive = mesh.primitives[0];

		if (primitive.mode != TINYGLTF_MODE_TRIANGLES)
		{
			qDebug() << "LoadMesh: " << "primitive.mode != TINYGLTF_MODE_TRIANGLES";
		}
		LVertexLayout layout;
		layout.stride = 8 * sizeof(float);
		std::vector<float> vertices;
		std::vector<uint32_t> indices;
		//layout(location = 0) in vec3 aPos;
		//layout(location = 1) in vec3 aNormal;
		//layout(location = 2) in vec2 aUv;

		layout.elements.resize(3);
		{
			auto acc = model.accessors[primitive.attributes["POSITION"]];
			accs[0] = acc;
			LVertexElement element;
			element.type = GL_FLOAT;
			element.index = 0;
			element.size = 3;
			element.offset = 0;
			layout.elements[0] = element;
			auto vertexCount = accs[0].count;
			vertices.resize(vertexCount * 8);
			tinygltf::BufferView bufferView = model.bufferViews[accs[0].bufferView];
			tinygltf::Buffer& buffer = model.buffers.at(bufferView.buffer);
			size_t byteStride = bufferView.byteStride;
			unsigned char* data = buffer.data.data() + bufferView.byteOffset + accs[0].byteOffset;
			for (size_t i = 0; i < accs[0].count; ++i)
			{
				vertices[i * 8 + 0] = *(float*)(data + i * byteStride + 0);
				vertices[i * 8 + 1] = *(float*)(data + i * byteStride + 4);
				vertices[i * 8 + 2] = *(float*)(data + i * byteStride + 8);
			}
		}
		{
			auto acc = model.accessors[primitive.attributes["NORMAL"]];
			accs[1] = acc;
			LVertexElement element;
			element.type = GL_FLOAT;
			element.index = 1;
			element.size = 3;
			element.offset = 3;
			layout.elements[1] = element;
			tinygltf::BufferView bufferView = model.bufferViews[accs[1].bufferView];
			tinygltf::Buffer& buffer = model.buffers.at(bufferView.buffer);
			size_t byteStride = bufferView.byteStride;
			unsigned char* data = buffer.data.data() + bufferView.byteOffset + accs[1].byteOffset;
			for (size_t i = 0; i < accs[1].count; ++i)
			{
				vertices[i * 8 + 3] = *(float*)(data + i * byteStride + 0);
				vertices[i * 8 + 4] = *(float*)(data + i * byteStride + 4);
				vertices[i * 8 + 5] = *(float*)(data + i * byteStride + 8);
			}
		}
		{
			auto acc = model.accessors[primitive.attributes["TEXCOORD_0"]];
			accs[2] = acc;
			LVertexElement element;
			element.type = GL_FLOAT;
			element.index = 2;
			element.size = 2;
			element.offset = 6;
			layout.elements[2] = element;
			tinygltf::BufferView bufferView = model.bufferViews[accs[2].bufferView];
			tinygltf::Buffer& buffer = model.buffers.at(bufferView.buffer);
			size_t byteStride = bufferView.byteStride;
			unsigned char* data = buffer.data.data() + bufferView.byteOffset + accs[2].byteOffset;
			for (size_t i = 0; i < accs[2].count; ++i)
			{
				vertices[i * 8 + 6] = *(float*)(data + i * byteStride + 0);
				vertices[i * 8 + 7] = *(float*)(data + i * byteStride + 4);
			}
		}
		// indices
		{
			const auto& accessor = model.accessors[primitive.indices];
			const auto& bufferView = model.bufferViews[accessor.bufferView];
			const auto& buffer = model.buffers[bufferView.buffer];

			const void* dataPtr =
				&buffer.data[bufferView.byteOffset + accessor.byteOffset];

			indices.resize(accessor.count);

			if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
			{
				const uint16_t* src = reinterpret_cast<const uint16_t*>(dataPtr);
				for (size_t i = 0; i < accessor.count; ++i)
					indices[i] = src[i];
			}
			else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
			{
				memcpy(indices.data(), dataPtr, accessor.count * sizeof(uint32_t));
			}
		}
		ret = std::make_shared<LMesh>(layout, vertices, indices);
		return ret;
	}

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
		this->m_vertices = vertices;
		this->m_indices = indices;
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

	const std::vector<float>& LMesh::GetVertices() const
	{
		return m_vertices;
	}

	const std::vector<uint32_t>& LMesh::GetIndices() const
	{
		return m_indices;
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
