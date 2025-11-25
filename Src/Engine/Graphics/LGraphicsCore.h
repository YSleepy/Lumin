#pragma once

#include <memory>

#include "LShader.h"
#include "Render/LMaterial.h"
#include "Render/LMesh.h"

namespace Lumin
{
	class LGraphicsCore
	{
	public:
		std::shared_ptr<LShader> CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource);
		GLuint CreateVertexBufferObject(const std::vector<float>& vertices);
		GLuint CreateIndexBufferObject(const std::vector<unsigned int>& indices);
		void SetClearColor(float r, float g, float b, float a);
		void ClearBuffers();
		void BindShader(LShader* shader);
		void BindMaterial(LMaterial* material);
		void BindMesh(LMesh* mesh);
		void DrawMesh(LMesh* mesh);


	};

}

