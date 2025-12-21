#pragma once
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace EngineRuntime
{
	class LCommand;

	class LCommandRegistry
	{
	public:
		using Factory = std::function<std::unique_ptr<LCommand>()>;
		static LCommandRegistry& Instance();
		void Register(const char* name, Factory factory);
		const std::unordered_map<std::string, Factory>& GetAll() const;

	private:
		std::unordered_map<std::string, Factory> m_factories;
	};

#define REGISTER_COMMAND(CommandType)                        \
    namespace                                                \
    {                                                        \
        struct CommandType##_AutoRegister                    \
        {                                                    \
            CommandType##_AutoRegister()                     \
            {                                                \
                EngineRuntime::LCommandRegistry::Instance().Register(\
                    #CommandType,                            \
                    []() { return std::make_unique<CommandType>(); } \
                );                                           \
            }                                                \
        };                                                   \
        static CommandType##_AutoRegister                    \
            CommandType##_autoRegisterInstance;              \
    }
}
