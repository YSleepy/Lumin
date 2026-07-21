#include "GSceneComponent.h"
#include "GamePlay/GActor.h"

namespace Lumin
{
	GSceneComponent::GSceneComponent(std::string name) : GComponent(name)
	{
	}

	GSceneComponent::~GSceneComponent()
	{
	}

	void GSceneComponent::Tick(float deltaTime)
	{
	}

	void GSceneComponent::SetPosition(const QVector3D& position)
	{
		m_localTransform.position = position;
	}

	QVector3D GSceneComponent::GetPosition()
	{
		return m_localTransform.position;
	}

	QVector3D GSceneComponent::GetWorldPosition()
	{
		// The origin undergoes world transformation to obtain the world position
		auto ret = GetWorldTransform().map(QVector4D(0, 0, 0, 1));
		return ret.toVector3D() / ret.w();
	}

	void GSceneComponent::SetRotation(const QQuaternion& rotation)
	{
		m_localTransform.rotation = rotation;
	}

	QQuaternion GSceneComponent::GetRotation()
	{
		return m_localTransform.rotation;
	}

	void GSceneComponent::SetScale(const QVector3D& scale)
	{
		m_localTransform.scale = scale;
	}

	QVector3D GSceneComponent::GetScale()
	{
		return m_localTransform.scale;
	}

	QMatrix4x4 GSceneComponent::GetLocalTransform()
	{
		QMatrix4x4 ret;
		ret.inverted();
		ret.translate(m_localTransform.position);
		ret.rotate(m_localTransform.rotation);
		ret.scale(m_localTransform.scale);
		return ret;
	}

	QMatrix4x4 GSceneComponent::GetWorldTransform()
	{
		return GetOwner()->GetWorldTransform() * GetLocalTransform();
	}
}

