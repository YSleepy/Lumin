#pragma once

#include <memory>

#include "LShader.h"
#include "Render/LMaterial.h"

namespace Lumin
{
	class LGraphicsCore
	{
	public:
		std::shared_ptr<LShader> CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource);
		void BindShader(LShader* shader);
		void BindMaterial(LMaterial* material);
	};

}

