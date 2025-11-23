#define LOG_TAG "LShader"

#include "LShader.h"

#include "LLog.h"

namespace Lumin
{
	LShader::LShader(GLuint programID)
	{
		CHECK_CONDITION_RETURN(programID != 0, "Invalid program ID");
		m_programID = programID;
	}

	LShader::~LShader()
	{
		glDeleteProgram(m_programID);
	}

	void LShader::Bind()
	{
		CHECK_CONDITION_RETURN(m_programID != 0, "Shader not compiled");
		glUseProgram(m_programID);
	}

	GLint LShader::GetUniformLocation(const std::string& name)
	{
		CHECK_CONDITION_RETURN_VALUE(m_programID != 0, -1, "Shader not compiled");
		CHECK_CONDITION_RETURN_VALUE(!name.empty(), -1, "Empty name");

		auto it = m_uniformLocationsCache.find(name);
		if (it != m_uniformLocationsCache.end())
		{
			return it->second;
		}
		GLint id = glGetUniformLocation(m_programID, name.c_str());
		CHECK_CONDITION_RETURN_VALUE(id != -1, -1, "Uniform location not found");

		m_uniformLocationsCache[name] = id;
		return id;
	}

	void LShader::SetUniform(const std::string& name, float value)
	{
		auto id = GetUniformLocation(name);
		glUniform1f(id, value);
	}
}
