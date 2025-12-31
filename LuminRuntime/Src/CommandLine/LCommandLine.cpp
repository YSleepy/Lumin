#include "LCommandLine.h"

#include <QDebug>

#include "LCommand.h"
#include "LCommandRegistry.h"

namespace EngineRuntime
{
	LCommandLine::LCommandLine()
	{
		for (auto& [name, factory] :
			LCommandRegistry::Instance().GetAll())
		{
			RegisterCommand(factory());
		}
	}

	LCommandLine::~LCommandLine()
	{
	}

	LCommandLine LCommandLine::Parse(int argc, char* argv[])
	{
		LCommandLine cmd;

		if (argc >= 2)
		{
			cmd.m_commandName = argv[1];
			for (int i = 2; i < argc; ++i)
				cmd.m_args << argv[i];
		}

		return cmd;
	}

	void LCommandLine::RegisterCommand(std::unique_ptr<LCommand> command)
	{
		m_commands.emplace(command->GetName(), std::move(command));
	}

	int LCommandLine::Dispatch()
	{
		if (m_commandName.isEmpty())
		{
			const QStringList args = {"default"};
			return m_commands.find("run")->second->Execute(args);
		}

		auto it = m_commands.find(m_commandName);
		if (it == m_commands.end())
		{
			qWarning() << "Unknown command:" << m_commandName;
			return -1;
		}

		return it->second->Execute(m_args);
	}

	bool LCommandLine::IsEmpty() const
	{
		return m_commandName.isEmpty();
	}
}
