#include "LCommandRegistry.h"

namespace EngineRuntime
{
	LCommandRegistry& LCommandRegistry::Instance()
	{
		static LCommandRegistry inst;
		return inst;
	}

	void LCommandRegistry::Register(const char* name, Factory factory)
	{
		m_factories.emplace(name, std::move(factory));
	}

	const std::unordered_map<std::string, LCommandRegistry::Factory>&
		LCommandRegistry::GetAll() const
	{
		return m_factories;
	}
}
