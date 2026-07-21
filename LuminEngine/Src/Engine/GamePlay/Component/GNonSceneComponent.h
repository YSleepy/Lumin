#pragma once
#include "GComponent.h"

namespace Lumin
{
	class GNonSceneComponent : public GComponent
	{
	public:
		GNonSceneComponent(std::string name);
		~GNonSceneComponent() override;
		void Tick(float deltaTime) override;
	};
}


