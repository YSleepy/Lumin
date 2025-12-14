#pragma once
#include "GController.h"

namespace Lumin
{
	class GPlayerController : public GController
	{
	public:
		void Tick(float deltaTime) override;
	private:
		float m_mouseSensitivity = 10.f;
		float m_speed = 1.f;
	};

}

