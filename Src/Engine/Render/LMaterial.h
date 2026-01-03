#pragma once
#include <memory>
#include <unordered_map>
#include <QVector2D>
#include <QMatrix4x4>

#include "Graphics/LShader.h"
#include "pre.h"

namespace Lumin
{
	class LTexture;
	class ENGINE_API LMaterial
	{
	public:
		LMaterial();
		LMaterial(const LMaterial&) = delete;
		LMaterial& operator=(const LMaterial&) = delete;
		~LMaterial();

		static std::shared_ptr<LMaterial> LoadMaterial(const char* path);
		void SetShader(const std::shared_ptr<LShader>& shader);
		void SetFloatParam(const std::string& name, float value);
		void Set2FloatParam(const std::string& name, float x, float y);
		void Set2FloatParam(const std::string& name, const QVector2D& vector);
		void Set3FloatParam(const std::string& name, float x, float y, float z);
		void Set3FloatParam(const std::string& name, const QVector3D& vector);
		void Set4MatrixParam(const std::string& name, const QMatrix4x4& matrix);
		void SetTexture(const std::string& name, const std::shared_ptr<LTexture>& texture);
		void Bind();
	private:
		std::shared_ptr<LShader> m_shader;
		std::unordered_map<std::string, float> m_floatParams;
		std::unordered_map<std::string, QVector2D> m_2FloatParams;
		std::unordered_map<std::string, QVector3D> m_3FloatParams;
		std::unordered_map<std::string, QMatrix4x4> m_4matrixParams;
		std::unordered_map<std::string, std::shared_ptr<LTexture>> m_textures;
	};
}


