#include "EGameInstance.h"

#include <QDebug>

bool EGameInstance::Init()
{
	return true;
}

void EGameInstance::Tick(float deltaTime)
{
	qDebug() << "GameInstance Tick deltaTime:" << deltaTime;
}

void EGameInstance::Destroy()
{
}
