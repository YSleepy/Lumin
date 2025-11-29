#include "EGameInstance.h"

#include <QDebug>
#include <QEvent>

#include "LEngine.h"


bool EGameInstance::Init()
{
	qDebug() << "EGameInstance Init";
	// 创建着色器程序
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
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
	m_firstMaterial.SetShader(shader);

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
	m_firstMesh = std::make_unique<Lumin::LMesh>(vertexLayout, vertices, indices);
	return true;
}

void EGameInstance::Tick(float deltaTime)
{
	if (Lumin::LEngine::GetInstance().GetInputManager().IsKeyPressed(Qt::Key_A))
	{
		qDebug() << "GameInstance Tick deltaTime:" << deltaTime;
		Lumin::LMeshSceneComponent sc;
		sc.m_material = &m_firstMaterial;
		sc.m_mesh = m_firstMesh.get();
		Lumin::RenderObj ro;
		ro.renderSceneComponent = sc;
		auto& renderQueue = Lumin::LEngine::GetInstance().GetRenderQueue();
		renderQueue.Submit(ro);
	}

	//std::this_thread::sleep_for(std::chrono::milliseconds(16));
}

void EGameInstance::Destroy()
{
}
