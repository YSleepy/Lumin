#include "RunProjectCommand.h"

#include "LGameModuleBase.h"
#include "LEngine.h"
#include "CommandLine/LCommandRegistry.h"
#include "Loader/LProjectLoader.h"
#include "Loader/RunEngineWithProject.h"

namespace EngineRuntime
{
	REGISTER_COMMAND(RunProjectCommand);
	const char* RunProjectCommand::GetDescription() const
	{
		return "Run a project";
	}

	int RunProjectCommand::Execute(const QStringList& args)
	{
		if (args.isEmpty())
		{
			qWarning() << "No project specified";
			return -1;
		}

		LProjectLoader loader;
		if (!loader.LoadProject(args[0]))
		{
			qWarning() << "Failed to load project";
		}

		RunEngineWithProject(&loader);
		return 0;
	}
}
