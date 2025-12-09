#include "GComponent.h"

namespace Lumin
{
	GComponent::GComponent(const std::string& name)
	{
		m_name = name;
	}

	GActor* GComponent::GetOwner() const
	{
		return m_owner;
	}

	void GComponent::SetOwner(GActor* owner)
	{
		m_owner = owner;
	}

	const std::string& GComponent::GetName() const
	{
		return m_name;
	}

}
