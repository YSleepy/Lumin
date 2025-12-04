#pragma once
#include <memory>
#include <vector>

#include "GObject.h"

namespace Lumin
{
	class GActor : public GObject
	{
	public:
		virtual void Tick(float deltaTime);
		void SetName(const std::string name);
		std::string GetName();
		void SetParent(GActor* parent);
		GActor* GetParent();
		bool GetIsAlive();
		void MarkNextFrameDestruction();
	private:
		GActor* m_parent = nullptr;
		std::vector<std::unique_ptr<GActor>> m_children;
		bool m_isAlive = true;

		friend class GLevel;
	};
}

