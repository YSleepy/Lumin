#include "CreateProjectCommand.h"

#include <QDebug>

#include "Loader/LProjectTool.h"
#include "CommandLine/LCommandRegistry.h"


namespace EngineRuntime
{
	REGISTER_COMMAND(CreateProjectCommand);

	const char* CreateProjectCommand::GetDescription() const
	{
		return "Create a new game project";
	}

	int CreateProjectCommand::Execute(const QStringList& args)
	{
		if (args.size() < 2)
		{
			qWarning() << "Usage: new <ProjectName> <Path>";
			return -1;
		}

		if (!LProjectTool::CreateProject(args[0], args[1]))
		{
			qWarning() << "Failed to create project";
			return -1;
		}

		qDebug() << "Project created:" << args[0];
		return 0;
	}
}
