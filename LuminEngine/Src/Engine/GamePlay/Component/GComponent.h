#pragma once
#include "pre.h"
#include <string>

namespace Lumin
{
	class GActor;
	class ENGINE_API GComponent
	{
	public:
		GComponent(const std::string& name);
		virtual ~GComponent();
		virtual void Tick(float deltaTime) = 0;
		GActor* GetOwner() const;
		void SetOwner(GActor* owner);
		const std::string& GetName() const;
	protected:
		GActor* m_owner = nullptr;
		std::string m_name;
	};
}


