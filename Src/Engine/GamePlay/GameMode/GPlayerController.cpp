#include "GPlayerController.h"

#include "LEngine.h"
#include "LLog.h"

namespace Lumin
{
	void GPlayerController::Tick(float deltaTime)
	{
		GController::Tick(deltaTime);
		// TODO: modify player controller
		auto& input = LEngine::GetInstance().GetInputManager();
		CHECK_PTR_RETURN(m_controlledActor, "No actor controlled");
		QVector3D rotation = m_controlledActor->GetRotation();
		qDebug() << "Rotation1: " << rotation;
		if (input.IsButtonPressed(Qt::MouseButton::LeftButton))
		{
			const QVector2D& mouseOldPos = input.GetMouseOldPos();
			const QVector2D& mouseNewPos = input.GetMouseNewPos();
			QVector2D delta = mouseNewPos - mouseOldPos;
			rotation.setY(rotation.y() - delta.x() * m_mouseSensitivity * deltaTime);
			rotation.setX(rotation.x() - delta.y() * m_mouseSensitivity * deltaTime);
			m_controlledActor->SetRotation(rotation);
			qDebug() << "Rotation2: " << rotation;
		}
		QMatrix4x4 rotationMatrix(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
		rotationMatrix.rotate(rotation.x(), QVector3D(1.f, 0.f, 0.f));
		rotationMatrix.rotate(rotation.y(), QVector3D(0.f, 1.f, 0.f));
		rotationMatrix.rotate(rotation.z(), QVector3D(0.f, 0.f, 1.f));
		
		QVector3D forward = rotationMatrix.map(QVector3D(0.f, 0.f, -1.f));
		qDebug() << "Forward: " << forward;
		QVector3D right = rotationMatrix.map(QVector3D(1.f, 0.f, 0.f));
		qDebug() << "Right: " << right;

		auto pos = m_controlledActor->GetPosition();

		if (LEngine::GetInstance().GetInputManager().IsKeyPressed(Qt::Key_A))
		{
			pos -= right * m_speed * deltaTime;
		}
		else if (LEngine::GetInstance().GetInputManager().IsKeyPressed(Qt::Key_D))
		{
			pos += right * m_speed * deltaTime;
		}
		if (LEngine::GetInstance().GetInputManager().IsKeyPressed(Qt::Key_W))
		{
			pos += forward * m_speed * deltaTime;
		}
		else if (LEngine::GetInstance().GetInputManager().IsKeyPressed(Qt::Key_S))
		{
			pos -= forward * m_speed * deltaTime;
		}
		m_controlledActor->SetPosition(pos);
	}
}

