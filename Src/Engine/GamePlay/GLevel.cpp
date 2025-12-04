#include "GLevel.h"

#include "LLog.h"

namespace Lumin
{
	void GLevel::Tick(float deltaTime)
	{
		for (auto it = m_actors.begin(); it != m_actors.end();)
		{
			if ((*it)->GetIsAlive())
			{
				(*it)->Tick(deltaTime);
				++it;
			}
			else
			{
				it = m_actors.erase(it);
			}
		}
	}

	void GLevel::Clear()
	{
		m_actors.clear();
	}

	bool GLevel::SetActorParent(GActor* actor, GActor* parent)
	{
		CHECK_PTR_RETURN_VALUE(actor, false, "actor is null");
		bool result = false;
		auto currentParent = actor->GetParent();
		if (parent == nullptr) // move to root
		{
			if (currentParent != nullptr) // move from parent
			{
				auto it = std::find_if(
					currentParent->m_children.begin(),
					currentParent->m_children.end(),
					[actor](const std::unique_ptr<GActor>& e)
					{
						return e.get() == actor;
					}
				);
				if (it != currentParent->m_children.end())
				{
					m_actors.push_back(std::move(*it));
					actor->SetParent(nullptr);
					currentParent->m_children.erase(it);
					result = true;
				}
			}
			else // already root or just created
			{
				auto it = std::find_if(
					m_actors.begin(),
					m_actors.end(),
					[actor](const std::unique_ptr<GActor>& e)
					{
						return e.get() == actor;
					}
				);
				if (it == m_actors.end()) // just created
				{
					m_actors.push_back(std::unique_ptr<GActor>(actor));
					result = true;
				}
			}
		}
		else // move to parent
		{
			if (currentParent != nullptr)
			{
				auto it = std::find_if(
					currentParent->m_children.begin(),
					currentParent->m_children.end(),
					[actor](const std::unique_ptr<GActor> &e)
					{
						return e.get() == actor;
					}
				);
				if (it != currentParent->m_children.end()) // move from parent
				{
					bool found = false;
					auto currentElement = parent;
					while (currentElement)
					{
						if (currentElement == actor)
						{
							found = true; // can't move to self or child
							break;
						}
						currentElement = currentElement->GetParent();
					}
					if (!found)
					{
						m_actors.push_back(std::move(*it));
						actor->SetParent(parent);
						currentParent->m_children.erase(it);
						result = true;
					}
				}
			}
			else // already root or just created
			{
				auto it = std::find_if(
					m_actors.begin(),
					m_actors.end(),
					[actor](const std::unique_ptr<GActor>& e)
					{
						return e.get() == actor;
					}
				);
				if (it == m_actors.end()) // just created
				{
					parent->m_children.push_back(std::unique_ptr<GActor>(actor));
					actor->SetParent(parent);
					result = true;
				}
				else // already root
				{
					bool found = false;
					auto currentElement = parent;
					while (currentElement)
					{
						if (currentElement == actor)
						{
							found = true; // can't move to self or child
							break;
						}
						currentElement = currentElement->GetParent();
					}
					if (!found)
					{
						parent->m_children.push_back(std::move(*it));
						actor->SetParent(parent);
						m_actors.erase(it);
						result = true;
					}
				}
			}

		}
		return result;
	}

	GActor* GLevel::CreateActor(const std::string& name, GActor* parent)
	{
		GActor* actor = new GActor();
		actor->SetName(name);
		actor->SetParent(parent);
		if (parent == nullptr)
		{
			m_actors.push_back(std::unique_ptr<GActor>(actor));
		}
		return actor;
	}
}
