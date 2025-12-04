#include "GActor.h"

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
			}else
			{
				it = m_children.erase(it);
			}
		}
	}

	void GActor::SetName(const std::string name)
	{
		this->m_objectName = name;
	}

	std::string GActor::GetName()
	{
		return m_objectName;
	}

	void GActor::SetParent(GActor* parent)
	{
		m_parent = parent;
	}

	GActor* GActor::GetParent()
	{
		return m_parent;
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
