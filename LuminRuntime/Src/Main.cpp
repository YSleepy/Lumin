#include "CommandLine/LCommandLine.h"
#include "Engine/LApp.h"
#include "Log/LLog.h"

int main(int argc, char* argv[])
{
	Lumin::LApp app(argc, argv);
	Lumin::InitLog();

	auto cmd = EngineRuntime::LCommandLine::Parse(argc, argv);
	cmd.Dispatch();
	return 0;
}
