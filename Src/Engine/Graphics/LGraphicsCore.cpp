#define LOG_TAG "LGraphicsCore"

#include "LGraphicsCore.h"

#include "LLog.h"

namespace Lumin
{

	std::shared_ptr<LShader> LGraphicsCore::CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		CHECK_PTR_RETURN_VALUE(vertexShaderSource, nullptr, "vertexShaderSource is null");
		CHECK_PTR_RETURN_VALUE(fragmentShaderSource, nullptr, "fragmentShaderSource is null");
		return std::make_shared<LShader>(vertexShaderSource, fragmentShaderSource);
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
}
