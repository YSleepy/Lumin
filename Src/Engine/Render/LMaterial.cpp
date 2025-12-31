#define LOG_TAG "LMaterial"
#include "LMaterial.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "LLog.h"
#include "LEngine.h"
#include "Graphics/LTexture.h"
#include "FileSystem/LFileSystem.h"
#include "Graphics/LGraphicsCore.h"

namespace Lumin
{
	static const int FLOAT_COUNT = 3;
	static const char* SHADER = "shader";
	static const char* VERTEX_SHADER = "vertexShader";
	static const char* FRAGMENT_SHADER = "fragmentShader";
	static const char* PARAMS = "params";
	static const char* FLOATS[FLOAT_COUNT] = { "float", "float2", "float3" };
	static const char* TEXTURES = "textures";
	static const char* NAME = "name";
	static const char* PATH = "path";
	static const char* VALUE[FLOAT_COUNT] = { "value", "value2", "value3" };

	LMaterial::LMaterial()
	{
	}

	LMaterial::~LMaterial()
	{
	}

	namespace
	{
		void ParseShader(LMaterial* material, const QJsonObject& obj)
		{
			auto shaderObj = obj[SHADER].toObject();
			QString vsPath = shaderObj[VERTEX_SHADER].toString();
			QString fsPath = shaderObj[FRAGMENT_SHADER].toString();
			auto graphicsCore = LEngine::GetInstance().GetGraphicsCore();
			auto shader = graphicsCore.CreateShaderByFile(vsPath.toStdString().c_str(), fsPath.toStdString().c_str());
			material->SetShader(shader);
		}

		void ParseTextures(LMaterial* material, const QJsonObject& obj)
		{
			CHECK_CONDITION_RETURN(obj.contains(PARAMS), "obj does not contain params");
			auto paramsObj = obj[PARAMS].toObject();
			CHECK_CONDITION_RETURN(paramsObj.contains(TEXTURES), "obj does not contain textures");
			auto texturesArray = paramsObj[TEXTURES].toArray();
			for (const auto& param : texturesArray)
			{
				auto texture = param.toObject();
				QString name = texture[NAME].toString();
				QString texturePath = texture[PATH].toString();
				auto textureObj = LTexture::LoadTextureRGBA8(texturePath.toStdString().c_str());
				material->SetTexture(name.toStdString(), textureObj);
			}
		}

		void ParseParams(LMaterial* material, const QJsonObject& obj)
		{
			CHECK_CONDITION_RETURN(obj.contains(PARAMS), "obj does not contain params");
			auto paramsObj = obj[PARAMS].toObject();
			for (int i = 0; i < FLOAT_COUNT; ++i)
			{
				const char* & param = FLOATS[i];
				CHECK_CONDITION_RETURN(paramsObj.contains(param), "obj does not contain param array");
				auto floatArray = paramsObj[param].toArray();
				for (const auto& floatObj : floatArray)
				{
					auto floatParam = floatObj.toObject();
					if (strcmp(param, "float") == 0)
					{
						material->SetFloatParam(
							floatParam[NAME].toString().toStdString(),
							floatParam[VALUE[0]].toDouble()
						);
					}
					else if (strcmp(param, "float2") == 0)
					{
						material->Set2FloatParam(
							floatParam[NAME].toString().toStdString(),
							floatParam[VALUE[0]].toDouble(),
							floatParam[VALUE[1]].toDouble()
						);
					}
					else if (strcmp(param, "float3") == 0)
					{
						material->Set3FloatParam(
							floatParam[NAME].toString().toStdString(),
							floatParam[VALUE[0]].toDouble(),
							floatParam[VALUE[1]].toDouble(),
							floatParam[VALUE[2]].toDouble()
						);
					}
				}
			}
		}
	}

	std::shared_ptr<LMaterial> LMaterial::LoadMaterial(const char* path)
	{
		auto content = LFileSystem::LoadEngineAssetFileContents(path);
		if (content.isEmpty())
		{
			qDebug() << "Failed to load material file:" << path;
		}
		QJsonParseError parseError;
		QJsonDocument doc = QJsonDocument::fromJson(content, &parseError);
		if (parseError.error != QJsonParseError::NoError)
		{
			qDebug() << "Failed to parse material file:" << path;
			qDebug() << parseError.errorString();
		}
		QJsonObject obj = doc.object();
		std::shared_ptr<LMaterial> materialReturn = std::make_shared<LMaterial>();
		ParseShader(materialReturn.get(), obj);
		ParseTextures(materialReturn.get(), obj);
		ParseParams(materialReturn.get(), obj);
		return materialReturn;
	}

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

	void LMaterial::SetTexture(const std::string& name, const std::shared_ptr<LTexture>& texture)
	{
		m_textures[name] = texture;
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
		for (auto& param : m_textures)
		{
			m_shader->SetTexture(param.first, param.second.get());
		}
	}
}
