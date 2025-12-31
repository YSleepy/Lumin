#include "EActor.h"

#include <memory>
#include <vector>
#include <QDebug>
#include <thread>
#include <QImage>
#include <QOpenGLFunctions_3_3_Core>

#include "Engine/LEngine.h"
#include "Engine/GamePlay/GActor.h"
#include "Engine/Graphics/LGraphicsCore.h"
#include "Engine/Graphics/LTexture.h"
#include "Engine/GamePlay/Component/GMeshSceneComponent.h"
#include "FileSystem/LFileSystem.h"

namespace DefaultGameMode
{
	EActor::EActor()
	{
		qDebug() << "EGameInstance Init";
		// 创建着色器程序
		auto& graphics = Lumin::LEngine::GetInstance().GetGraphicsCore();
		auto mesh = Lumin::LMesh::LoadMesh("/Mesh/earth_globe8k_gltf_extracted/scene.gltf");
		auto material = Lumin::LMaterial::LoadMaterial("/Materials/Mat_Earth.json");

		AddCommponent(new Lumin::GMeshSceneComponent(mesh, material, "MeshComponent"));
	}

	void EActor::Tick(float deltaTime)
	{
		Lumin::GActor::Tick(deltaTime);
		qDebug() << "GameInstance Tick deltaTime:" << deltaTime;

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

}
