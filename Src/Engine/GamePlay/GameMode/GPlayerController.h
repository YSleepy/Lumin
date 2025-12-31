#pragma once
#include "GController.h"
#include "pre.h"

namespace Lumin
{
	class ENGINE_API GPlayerController : public GController
	{
	public:
		void Tick(float deltaTime) override;
		void SetMouseSensitivity(float sensitivity);
		void SetSpeed(float speed);
	private:
		float m_mouseSensitivity = 10.f;
		float m_speed = 1.f;
	};

}

