#pragma once
#include <QMatrix4x4>

#include "GComponent.h"

namespace Lumin
{
	class GCameraComponent : public GComponent
	{
	public:
		GCameraComponent(const std::string& name);
		QMatrix4x4 GetViewMatrix() const;
		QMatrix4x4 GetProjectionMatrix() const;
		void Tick(float deltaTime) override;

	};

}

