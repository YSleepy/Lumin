#pragma once
#include "GComponent.h"
#include "Common.h"

namespace Lumin
{
	class GSceneComponent : public GComponent
	{
	public:
		GSceneComponent(std::string name);
		~GSceneComponent() override;
		void Tick(float deltaTime) override;
		void SetPosition(const QVector3D& position);
		QVector3D GetPosition();
		QVector3D GetWorldPosition();
		void SetRotation(const QQuaternion& rotation);
		QQuaternion GetRotation();
		void SetScale(const QVector3D& scale);
		QVector3D GetScale();
		QMatrix4x4 GetLocalTransform(); // Transformation relative to the coordinate system of the parent node
		QMatrix4x4 GetWorldTransform(); // Transformation relative to the world coordinate system

	protected:
		LTransform  m_localTransform;
	};
}


