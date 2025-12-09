#include "GCameraComponent.h"
#include "GamePlay/GActor.h"

namespace Lumin
{
	GCameraComponent::GCameraComponent(const std::string& name): GComponent(name)
	{
	}

	QMatrix4x4 GCameraComponent::GetViewMatrix() const
	{
		return GetOwner()->GetWorldTransform().inverted();
	}

	QMatrix4x4 GCameraComponent::GetProjectionMatrix() const
	{
		return QMatrix4x4();
	}

	void GCameraComponent::Tick(float deltaTime)
	{
	}
}
