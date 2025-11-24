#define LOG_TAG "LMaterial"
#include "LMaterial.h"

#include "LLog.h"
namespace Lumin
{
	void LMaterial::SetShader(const std::shared_ptr<LShader>& shader)
	{
		m_shader = shader;
	}

	void LMaterial::SetFloatParam(const std::string& name, float value)
	{
		m_floatParams[name] = value;
	}

	void LMaterial::Bind()
	{
		CHECK_PTR_RETURN(m_shader, "m_shader is null");
		m_shader->Bind();
		for (auto& param : m_floatParams)
		{
			m_shader->SetUniform(param.first, param.second);
		}
	}
}
