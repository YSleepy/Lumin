#include "HelpCommand.h"

#include <QDebug>

#include "CommandLine/LCommandRegistry.h"

namespace EngineRuntime
{
	REGISTER_COMMAND(HelpCommand);

	HelpCommand::~HelpCommand()
	{
	}

	const char* HelpCommand::GetDescription() const
	{
		return "Show help information";
	}

	int HelpCommand::Execute(const QStringList& args)
	{
		qDebug() << "Commands:";
		qDebug() << "  new <Name> <Path>     Create a new project";
		qDebug() << "  run <Project>  Run a project";
		qDebug() << "  help           Show help";
		return 0;
	}

}

