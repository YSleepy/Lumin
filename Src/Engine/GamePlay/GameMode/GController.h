#pragma once
#include "GamePlay/GActor.h"
#include "pre.h"

namespace Lumin
{
	class ENGINE_API GController: public GActor
	{
	public:
		virtual void Possess(GActor* actor);
		virtual void Unpossess();
		virtual void OnPossess(GActor* actor);
		virtual void OnUnpossess(GActor* actor);
		virtual void Tick(float deltaTime) override;
	protected:
		GActor* m_controlledActor = nullptr;
	};

}

