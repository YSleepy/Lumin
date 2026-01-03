#include "EGameInstance.h"

#include <QDebug>

#include "EActor.h"
#include "Engine/GamePlay/Component/GCameraComponent.h"
#include "GamePlay/Component/GLightComponent.h"

namespace DefaultGameMode
{
	bool EGameInstance::Init()
	{
		auto testActor = GetCurrentLevel()->CreateActor<EActor>("test");
		auto testPawn = GetCurrentLevel()->CreateActor("testCamera");
		auto testPlayerController = GetCurrentLevel()->CreateActor<Lumin::GPlayerController>("testPlayerController");
		testPlayerController->SetSpeed(9);
		testPawn->AddCommponent(new Lumin::GCameraComponent("testCameraComponent"));
		testPawn->SetPosition(QVector3D(0, 0, 10));
		GetCurrentLevel()->SetDefaultActor(testPawn);
		GetCurrentLevel()->SetDefaultPlayerController(testPlayerController);
		testPlayerController->Possess(testPawn);

		auto teseLight = GetCurrentLevel()->CreateActor("testLight");
		auto testLightComponent = new Lumin::GLightComponent("testLightComponent");
		testLightComponent->SetColor(0, 1, 0);
		teseLight->AddCommponent(testLightComponent);
		teseLight->SetPosition(QVector3D(0, 10, 0));

		return true;
	}

	void EGameInstance::Tick(float deltaTime)
	{
		LGameInstanceBase::Tick(deltaTime);
	}

	void EGameInstance::Destroy()
	{
	}

}
