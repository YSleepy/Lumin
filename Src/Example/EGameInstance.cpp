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
		"layout (location = 1) in vec3 aColor;\n"
		"uniform mat4 mvp;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = mvp * vec4(aPos, 1.0);\n"
		"   ourColor = aColor;\n"
		"}\n";

	const char* fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 ourColor;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(ourColor, 1.0);\n"
		"}\n";
	auto& graphics = Lumin::LEngine::GetInstance().GetGraphicsCore();
	auto shader = graphics.CreateShader(vertexShaderSource, fragmentShaderSource);
	m_firstMaterial.SetShader(shader);
	// 顶点数据：位置(x,y,z) + 颜色(r,g,b)
	std::vector<float> vertices = {
		// 顶点 0: 位置(-0.5, -0.5, 0.0)  颜色(1.0, 0.0, 0.0) -> 红色
		  -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

		  // 顶点 1: 位置( 0.5, -0.5, 0.0)  颜色(0.0, 1.0, 0.0) -> 绿色
		  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

		  // 顶点 2: 位置( 0.5,  0.5, 0.0)  颜色(0.0, 0.0, 1.0) -> 蓝色
		  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,

		  // 顶点 3: 位置(-0.5,  0.5, 0.0)  颜色(1.0, 1.0, 0.0) -> 黄色
		  -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
	};

	// 索引数组
	std::vector<unsigned int> indices = {
	0, 1, 2, // 第一个三角形：使用顶点 0, 1, 2
	0, 2, 3  // 第二个三角形：使用顶点 0, 2, 3
	};

	Lumin::LVertexLayout vertexLayout;
	vertexLayout.elements.push_back(
		{ 0, 3, GL_FLOAT, 0 }
	);
	vertexLayout.elements.push_back(
		{ 1, 3, GL_FLOAT, 3 * sizeof(float) }
	);
	vertexLayout.stride = 6 * sizeof(float);
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
		ro.renderSceneComponent = &sc;
		auto& renderQueue = Lumin::LEngine::GetInstance().GetRenderQueue();
		renderQueue.Submit(ro);
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void EGameInstance::Destroy()
{
}
