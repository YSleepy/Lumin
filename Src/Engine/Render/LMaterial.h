#pragma once
#include <memory>
#include <unordered_map>
#include <QVector2D>
#include <QMatrix4x4>

#include "Graphics/LShader.h"

namespace Lumin
{

	class LMaterial
	{
	public:
		void SetShader(const std::shared_ptr<LShader>& shader);
		void SetFloatParam(const std::string& name, float value);
		void Set2FloatParam(const std::string& name, float x, float y);
		void Set3FloatParam(const std::string& name, float x, float y, float z);
		void Set4MatrixParam(const std::string& name, const QMatrix4x4& matrix);
		void Bind();
	private:
		std::shared_ptr<LShader> m_shader;
		std::unordered_map<std::string, float> m_floatParams;
		std::unordered_map<std::string, QVector2D> m_2FloatParams;
		std::unordered_map<std::string, QVector3D> m_3FloatParams;
		std::unordered_map<std::string, QMatrix4x4> m_4matrixParams;
	};
}


