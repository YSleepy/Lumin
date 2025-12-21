#include "EGameInstance.h"

#include <QDebug>

#include "EActor.h"
#include "Engine/GamePlay/Component/GCameraComponent.h"

namespace DefaultGameMode
{
	bool EGameInstance::Init()
	{
		auto testActor = GetCurrentLevel()->CreateActor<EActor>("test");
		auto testPawn = GetCurrentLevel()->CreateActor("testCamera");
		auto testPlayerController = GetCurrentLevel()->CreateActor<Lumin::GPlayerController>("testPlayerController");
		testPawn->AddCommponent(new Lumin::GCameraComponent("testCameraComponent"));
		testPawn->SetPosition(QVector3D(0, 0, 10));
		GetCurrentLevel()->SetDefaultActor(testPawn);
		GetCurrentLevel()->SetDefaultPlayerController(testPlayerController);
		testPlayerController->Possess(testPawn);

		return true;
	}

	void EGameInstance::Tick(float deltaTime)
	{
		m_world.Tick(deltaTime);
	}

	void EGameInstance::Destroy()
	{
	}

}
