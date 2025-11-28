#define LOG_TAG "LShader"

#include "LShader.h"

#include "LLog.h"
#include "OpenGLApi/LOpenGLFunctionsManager.h"

namespace Lumin
{
	LShader::LShader(GLuint programID)
	{
		CHECK_CONDITION_RETURN(programID != 0, "Invalid program ID");
		m_programID = programID;
	}

	LShader::LShader(const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		GLuint vertexShader = L_GL->glCreateShader(GL_VERTEX_SHADER);
		L_GL->glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		L_GL->glCompileShader(vertexShader);
		// Check vertex shader
		GLint success;
		GLchar infoLog[512];
		L_GL->glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			L_GL->glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
			qWarning() << "Vertex shader compile failed:" << infoLog;
			L_GL->glDeleteShader(vertexShader);
			return;
		}

		GLuint fragmentShader = L_GL->glCreateShader(GL_FRAGMENT_SHADER);
		L_GL->glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		L_GL->glCompileShader(fragmentShader);
		L_GL->CheckOpenGLError();

		// Check fragment shader
		L_GL->glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			L_GL->glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
			qWarning() << "Fragment shader compile failed:" << infoLog;
			L_GL->glDeleteShader(vertexShader);
			L_GL->glDeleteShader(fragmentShader);
			return;
		}
		m_programID = L_GL->glCreateProgram();
		L_GL->glAttachShader(m_programID, vertexShader);
		L_GL->glAttachShader(m_programID, fragmentShader);
		L_GL->glLinkProgram(m_programID);

		// Check link program
		L_GL->glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
		if (!success) {
			L_GL->glGetProgramInfoLog(m_programID, 512, nullptr, infoLog);
			qWarning() << "Shader program link failed:" << infoLog;
			L_GL->glDeleteShader(vertexShader);
			L_GL->glDeleteShader(fragmentShader);
			L_GL->glDeleteProgram(m_programID);
			m_programID = 0;
			return;
		}
		L_GL->glDeleteShader(vertexShader);
		L_GL->glDeleteShader(fragmentShader);
	}

	LShader::~LShader()
	{
		L_GL->glDeleteProgram(m_programID);
	}

	void LShader::Bind()
	{
		CHECK_CONDITION_RETURN(m_programID != 0, "Shader not compiled");
		L_GL->glUseProgram(m_programID);
		L_GL->CheckOpenGLError();
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
		GLint id = L_GL->glGetUniformLocation(m_programID, name.c_str());
		CHECK_CONDITION_RETURN_VALUE(id != -1, -1, "Uniform location not found");

		m_uniformLocationsCache[name] = id;
		return id;
	}

	void LShader::SetUniform(const std::string& name, float value)
	{
		auto id = GetUniformLocation(name);
		L_GL->glUniform1f(id, value);
	}
}
