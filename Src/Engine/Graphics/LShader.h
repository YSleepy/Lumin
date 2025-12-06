#pragma once
#include <QOpenGLFunctions_3_3_Core>
#include <unordered_map>
#include <QVector2D>

namespace Lumin
{
	class LShader
	{
	public:
		LShader(GLuint programID);
		LShader(const char* vertexShaderSource, const char* fragmentShaderSource);
		// 期望着色器仅创建一次或删除一次，避免重复产生的问题
		LShader(const LShader&) = delete;
		LShader& operator=(const LShader&) = delete;
		~LShader();
		void Bind();
		GLint GetUniformLocation(const std::string& name);
		void SetUniform(const std::string& name, float value);
		void SetUniform(const std::string& name, const QVector2D& value);
		void SetUniform(const std::string& name, const QVector3D& value);
		void SetUniform(const std::string& name, const QMatrix4x4& value);

	private:
		GLuint m_programID = 0;
		// uniform变量的位置缓存
		std::unordered_map<std::string, GLuint> m_uniformLocationsCache;
	};
}


