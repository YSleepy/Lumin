#include "EGameInstance.h"

#include <QDebug>
#include <QEvent>

#include "LEngine.h"


bool EGameInstance::Init()
{
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


	return true;
}

void EGameInstance::Tick(float deltaTime)
{
	if (Lumin::LEngine::GetInstance().GetInputManager().IsKeyPressed(Qt::Key_A))
	{
		qDebug() << "GameInstance Tick deltaTime:" << deltaTime;
	}
}

void EGameInstance::Destroy()
{
}
