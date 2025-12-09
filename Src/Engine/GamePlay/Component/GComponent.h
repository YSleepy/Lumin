#pragma once
#include <string>

namespace Lumin
{
	class GActor;
	class GComponent
	{
	public:
		GComponent(const std::string& name);
		virtual ~GComponent() = default;
		virtual void Tick(float deltaTime) = 0;
		GActor* GetOwner() const;
		void SetOwner(GActor* owner);
		const std::string& GetName() const;
	protected:
		GActor* m_owner = nullptr;
		std::string m_name;
	};
}


