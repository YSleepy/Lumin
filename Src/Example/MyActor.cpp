#include "MyActor.h"
#include <LEngine.h>

#include "GamePlay/Component/GCameraComponent.h"
#include "GamePlay/Component/GMeshSceneComponent.h"

MyActor::MyActor()
{
	qDebug() << "EGameInstance Init";
	// 创建着色器程序
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 modelMatrix;\n"
		"uniform mat4 viewMatrix;\n"
		"uniform mat4 projectionMatrix;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
		"}\n";

	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n";
	auto& graphics = Lumin::LEngine::GetInstance().GetGraphicsCore();
	auto shader = graphics.CreateShader(vertexShaderSource, fragmentShaderSource);
	auto material = std::make_shared<Lumin::LMaterial>();
	material->SetShader(shader);

	std::vector<float> vertices = {
		  -0.5f, -0.5f, 0.0f,
		  0.5f, -0.5f, 0.0f,
		  0.5f, 0.5f, 0.0f,
		  -0.5f, 0.5f, 0.0f,
	};

	// 索引数组
	std::vector<unsigned int> indices = {
	0, 1, 2,
	0, 2, 3
	};

	Lumin::LVertexLayout vertexLayout;
	vertexLayout.elements.push_back(
		{ 0, 3, GL_FLOAT, 0 }
	);
	vertexLayout.stride = 3 * sizeof(float);
	auto mesh = std::make_shared<Lumin::LMesh>(vertexLayout, vertices, indices);
	
	AddCommponent(new Lumin::GMeshSceneComponent(mesh, material, "MeshComponent"));
}

void MyActor::Tick(float deltaTime)
{
	GActor::Tick(deltaTime);
	qDebug() << "GameInstance Tick deltaTime:" << deltaTime;


	std::this_thread::sleep_for(std::chrono::milliseconds(16));
}
