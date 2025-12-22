#include <thread>
#include <filesystem>
#include <QtGui/QSurfaceFormat>

#include "CommandLine/LCommandLine.h"
#include "Engine/LApp.h"
#include "Example/EGameInstance.h"
#include "Engine/LEngine.h"
#include "Log/LLog.h"


int main(int argc, char* argv[])
{
	Lumin::LApp app(argc, argv);
	Lumin::InitLog();

	auto cmd = EngineRuntime::LCommandLine::Parse(argc, argv);
	if (cmd.IsEmpty())
	{
		// use default project
	}
	cmd.Dispatch();
	return 0;
}
