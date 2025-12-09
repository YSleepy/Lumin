#include "EGameInstance.h"

#include <QDebug>
#include <QEvent>

#include "LEngine.h"
#include "MyActor.h"


bool EGameInstance::Init()
{
	auto a = GetCurrentLevel()->CreateActor<MyActor>("test");
	GetCurrentLevel()->SetDefaultActor(a);
	return true;
}

void EGameInstance::Tick(float deltaTime)
{
	m_world.Tick(deltaTime);
}

void EGameInstance::Destroy()
{
}

