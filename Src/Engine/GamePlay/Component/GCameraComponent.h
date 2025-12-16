#pragma once
#include "pre.h"
#include <QMatrix4x4>

#include "GComponent.h"

namespace Lumin
{
	class ENGINE_API GCameraComponent : public GComponent
	{
	public:
		GCameraComponent(const std::string& name);
		QMatrix4x4 GetViewMatrix() const;
		QMatrix4x4 GetProjectionMatrix(float aspect) const;
		void Tick(float deltaTime) override;
	private:
		float m_fov = 45.0f;
		float m_near = 0.1f;
		float m_far = 1000.0f;
	};

}

