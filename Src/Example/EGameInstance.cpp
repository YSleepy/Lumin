#include "EGameInstance.h"

#include <QDebug>
#include <QEvent>
#include "LEngine.h"

bool EGameInstance::Init()
{
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
