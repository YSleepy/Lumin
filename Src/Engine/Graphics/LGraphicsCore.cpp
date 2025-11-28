#define LOG_TAG "LGraphicsCore"

#include "LGraphicsCore.h"

#include "LLog.h"
#include "OpenGLApi/LOpenGLFunctionsManager.h"

namespace Lumin
{

	std::shared_ptr<LShader> LGraphicsCore::CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		CHECK_PTR_RETURN_VALUE(vertexShaderSource, nullptr, "vertexShaderSource is null");
		CHECK_PTR_RETURN_VALUE(fragmentShaderSource, nullptr, "fragmentShaderSource is null");
		return std::make_shared<LShader>(vertexShaderSource, fragmentShaderSource);
	}

	GLuint LGraphicsCore::CreateVertexBufferObject(const std::vector<float>& vertices)
	{
		GLuint vbo;
		L_GL->glGenBuffers(1, &vbo);
		L_GL->glBindBuffer(GL_ARRAY_BUFFER, vbo);
		L_GL->glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		L_GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
		return vbo;
	}

	GLuint LGraphicsCore::CreateIndexBufferObject(const std::vector<unsigned int>& indices)
	{
		GLuint ebo;
		L_GL->glGenBuffers(1, &ebo);
		L_GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		L_GL->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		L_GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		return ebo;
	}

	void LGraphicsCore::SetClearColor(float r, float g, float b, float a)
	{
		L_GL->glClearColor(r, g, b, a);
	}

	void LGraphicsCore::ClearBuffers()
	{
		L_GL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void LGraphicsCore::BindShader(LShader* shader)
	{
		CHECK_PTR_RETURN(shader, "shader is null");
		shader->Bind();
	}

	void LGraphicsCore::BindMaterial(LMaterial* material)
	{
		CHECK_PTR_RETURN(material, "material is null");
		material->Bind();
	}

	void LGraphicsCore::BindMesh(LMesh* mesh)
	{
		CHECK_PTR_RETURN(mesh, "mesh is null");
		qDebug() << "BindMesh mesh ptr = " << mesh;
		mesh->Bind();
	}

	void LGraphicsCore::DrawMesh(LMesh* mesh)
	{
		CHECK_PTR_RETURN(mesh, "mesh is null");
		mesh->Draw();
	}

}
