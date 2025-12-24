#include "EActor.h"

#include <memory>
#include <vector>
#include <QDebug>
#include <thread>
#include <QImage>
#include <QOpenGLFunctions_3_3_Core>

#include "Engine/LEngine.h"
#include "Engine/GamePlay/GActor.h"
#include "Engine/Graphics/LGraphicsCore.h"
#include "Engine/Graphics/LTexture.h"
#include "Engine/GamePlay/Component/GMeshSceneComponent.h"
#include "FileSystem/LFileSystem.h"

namespace DefaultGameMode
{
	EActor::EActor()
	{
		qDebug() << "EGameInstance Init";
		// 创建着色器程序
		const char* vertexShaderSource =
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec2 uv;\n"
			"out vec2 vUV;\n"
			"uniform mat4 modelMatrix;\n"
			"uniform mat4 viewMatrix;\n"
			"uniform mat4 projectionMatrix;\n"
			"void main()\n"
			"{\n"
			"   vUV = uv;\n"
			"   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
			"}\n";

		const char* fragmentShaderSource =
			"#version 330 core\n"
			"in vec2 vUV;\n"
			"out vec4 FragColor;\n"
			"uniform sampler2D aTexture;\n"
			"void main()\n"
			"{\n"
			"   FragColor = texture(aTexture, vUV);\n"
			"}\n";
		auto& graphics = Lumin::LEngine::GetInstance().GetGraphicsCore();
		auto shader = graphics.CreateShader(vertexShaderSource, fragmentShaderSource);
		// TODO: Materials and textures should be managed by the material system
		// TODO: resources should also be encapsulated accordingly

		auto texturePath = Lumin::LEngine::GetInstance().GetFileSystem().GetEngineAssetsPath() + "/shime15.png";
		QString texturePathStr(texturePath.c_str());
		QImage* sourceImage = new QImage(texturePathStr);
		QImage image = sourceImage->convertToFormat(QImage::Format_RGBA8888);
		image = image.mirrored(false, true);
		auto texture = std::make_shared<Lumin::LTexture>(image.size().width(), image.size().height(), 3, image.bits());
		auto material = std::make_shared<Lumin::LMaterial>();
		material->SetShader(shader);
		material->SetTexture("aTexture", texture);

		std::vector<float> vertices = {
			//vertex coords(3)  // texture coords (2)
			  0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
			  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
			  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
			  -0.5f, 0.5f, 0.0f, 0.0f, 1.0f // top left
		};

		// indices
		std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3
		};
		// vertex layout
		Lumin::LVertexLayout vertexLayout;
		vertexLayout.elements.push_back(
			{ 0, 3, GL_FLOAT, 0 }
		);
		// texture coords
		vertexLayout.elements.push_back(
			{ 1, 2, GL_FLOAT, 3 * sizeof(float) }
		);
		vertexLayout.stride = 5 * sizeof(float);
		auto mesh = std::make_shared<Lumin::LMesh>(vertexLayout, vertices, indices);

		AddCommponent(new Lumin::GMeshSceneComponent(mesh, material, "MeshComponent"));
	}

	void EActor::Tick(float deltaTime)
	{
		Lumin::GActor::Tick(deltaTime);
		qDebug() << "GameInstance Tick deltaTime:" << deltaTime;


		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

}
