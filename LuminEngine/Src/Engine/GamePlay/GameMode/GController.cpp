#include "GController.h"

#include "LLog.h"

namespace Lumin
{
	void GController::Possess(GActor* actor)
	{
		CHECK_PTR_RETURN(actor, "actor is null");
		if (m_controlledActor == actor)
		{
			qDebug("already possess actor");
			return;
		}
		m_controlledActor = actor;
		OnPossess(actor);
	}

	void GController::Unpossess()
	{
		CHECK_PTR_RETURN(m_controlledActor, "controlled actor is null");
		OnUnpossess(m_controlledActor);
		m_controlledActor = nullptr;
	}

	void GController::OnPossess(GActor* actor)
	{
	}

	void GController::OnUnpossess(GActor* actor)
	{
	}

	void GController::Tick(float deltaTime)
	{
		GActor::Tick(deltaTime);
	}
}
