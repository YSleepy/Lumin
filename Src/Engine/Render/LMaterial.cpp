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

	void LMaterial::Set2FloatParam(const std::string& name, float x, float y)
	{
		m_2FloatParams[name] = QVector2D(x, y);
	}

	void LMaterial::Set3FloatParam(const std::string& name, float x, float y, float z)
	{
		m_3FloatParams[name] = QVector3D(x, y, z);
	}

	void LMaterial::Set4MatrixParam(const std::string& name, const QMatrix4x4& matrix)
	{
		m_4matrixParams[name] = matrix;
	}


	void LMaterial::Bind()
	{
		CHECK_PTR_RETURN(m_shader, "m_shader is null");
		m_shader->Bind();
		for (auto& param : m_floatParams)
		{
			m_shader->SetUniform(param.first, param.second);
		}
		for (auto& param : m_2FloatParams)
		{
			m_shader->SetUniform(param.first, param.second);
		}
		for (auto& param : m_3FloatParams)
		{
			m_shader->SetUniform(param.first, param.second);
		}
		for (auto& param : m_4matrixParams)
		{
			m_shader->SetUniform(param.first, param.second);
		}
	}
}
