#pragma once
#include <memory>
#include <unordered_map>
#include <QStringList>

namespace EngineRuntime
{
	class LCommand;

	class LCommandLine
	{
	public:
		LCommandLine();
		~LCommandLine();
		LCommandLine(const LCommandLine&) = delete;
		LCommandLine& operator=(const LCommandLine&) = delete;
		LCommandLine(LCommandLine&&) noexcept = default;
		LCommandLine& operator=(LCommandLine&&) noexcept = default;
		static LCommandLine Parse(int argc, char* argv[]);
		void RegisterCommand(std::unique_ptr<LCommand> command);
		int Dispatch();
		bool IsEmpty() const;
	private:
		QString m_commandName;
		QStringList m_args;
		std::unordered_map<QString, std::unique_ptr<LCommand>> m_commands;
	};



}
