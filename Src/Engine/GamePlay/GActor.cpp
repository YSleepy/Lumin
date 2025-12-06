#include "GActor.h"

#include <QMatrix4x4>

#include "LLog.h"

namespace Lumin
{

	void GActor::Tick(float deltaTime)
	{
		for (auto it = m_children.begin(); it != m_children.end();)
		{
			if ((*it)->m_isAlive)
			{
				(*it)->Tick(deltaTime);
				++it;
			}
			else
			{
				it = m_children.erase(it);
			}
		}
	}

	void GActor::SetName(const std::string& name)
	{
		this->m_objectName = name;
	}

	std::string GActor::GetName()
	{
		return m_objectName;
	}

	void GActor::SetParent(GActor* parent)
	{
		// parent can be null
		m_parent = parent;
	}

	GActor* GActor::GetParent()
	{
		return m_parent;
	}

	void GActor::SetPosition(const QVector3D& position)
	{
		m_transform.position = position;
	}

	QVector3D GActor::GetPosition()
	{
		return m_transform.position;
	}

	void GActor::SetRotation(const QVector3D& rotation)
	{
		m_transform.rotation = rotation;
	}

	QVector3D GActor::GetRotation()
	{
		return m_transform.rotation;
	}

	void GActor::SetScale(const QVector3D& scale)
	{
		m_transform.scale = scale;
	}

	QVector3D GActor::GetScale()
	{
		return m_transform.scale;
	}

	QMatrix4x4 GActor::GetLocalTransform()
	{
		QMatrix4x4 transform = QMatrix4x4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
		transform.translate(m_transform.position);
		transform.rotate(m_transform.rotation.x(), QVector3D(1, 0, 0));
		transform.rotate(m_transform.rotation.y(), QVector3D(0, 1, 0));
		transform.rotate(m_transform.rotation.z(), QVector3D(0, 0, 1));
		transform.scale(m_transform.scale);
		qDebug() << "local transform: " << transform;
		return transform;
	}

	QMatrix4x4 GActor::GetWorldTransform()
	{
		if (m_parent)
		{
			return m_parent->GetWorldTransform() * GetLocalTransform();
		}
		return GetLocalTransform();
	}

	bool GActor::GetIsAlive()
	{
		return m_isAlive;
	}

	void GActor::MarkNextFrameDestruction()
	{
		m_isAlive = false;
	}
}
