#include "GCameraComponent.h"
#include "GamePlay/GActor.h"

namespace Lumin
{
	GCameraComponent::GCameraComponent(const std::string& name): GComponent(name)
	{
	}

	QMatrix4x4 GCameraComponent::GetViewMatrix() const
	{
		//| Xx  Yx  Zx  Tx |
		//| Xy  Yy  Zy  Ty |
		//| Xz  Yz  Zz  Tz |
		//|  0   0   0   1 |
		//	| column |       description        |
		//	| --------- | ----------------------|
		//	| column(0) | X (include scale)     |
		//	| column(1) | Y (include scale)     |
		//	| column(2) | Z (include scale)     |
		//	| column(3) | translation(Tx, Ty, Tz)|
		//	Remove scale through normalization

		QMatrix4x4 worldTransform = GetOwner()->GetWorldTransform();
		for (int i = 0; i <3; ++i)
		{
			QVector3D axis = worldTransform.column(i).toVector3D();
			axis.normalize();
			worldTransform.setColumn(i, QVector4D(axis, 0));
		}
		return worldTransform.inverted();
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
