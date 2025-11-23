#pragma once
#include <QOpenGLFunctions_3_3_Core>

#include <unordered_map>

namespace Lumin
{
	class LShader: public QOpenGLFunctions_3_3_Core
	{
	public:
		LShader(GLuint programID);
		// 期望着色器仅创建一次或删除一次，避免重复产生的问题
		LShader(const LShader&) = delete;
		LShader& operator=(const LShader&) = delete;
		~LShader();
		void Bind();
		GLint GetUniformLocation(const std::string& name);
		void SetUniform(const std::string& name, float value);

	private:
		GLuint m_programID = 0;
		// uniform变量的位置缓存
		std::unordered_map<std::string, GLuint> m_uniformLocationsCache;
	};
}


