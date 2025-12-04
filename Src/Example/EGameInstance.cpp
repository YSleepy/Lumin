#include "EGameInstance.h"

#include <QDebug>
#include <QEvent>

#include "LEngine.h"
#include "MyActor.h"


bool EGameInstance::Init()
{
	GetCurrentLevel()->CreateActor<MyActor>("test");
	return true;
}

void EGameInstance::Tick(float deltaTime)
{
	m_world.Tick(deltaTime);
}

void EGameInstance::Destroy()
{
}

Lumin::GLevel* EGameInstance::GetCurrentLevel()
{
	return m_world.GetCurrentLevel();
}

Lumin::GWorld* EGameInstance::GetWorld()
{
	return &m_world;
}
