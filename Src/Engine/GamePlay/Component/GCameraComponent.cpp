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

	QMatrix4x4 GCameraComponent::GetProjectionMatrix(float aspect) const
	{
		QMatrix4x4 projectionMatrix;
		projectionMatrix.perspective(m_fov, aspect, m_near, m_far);
		return projectionMatrix;
	}

	void GCameraComponent::Tick(float deltaTime)
	{
	}
}
