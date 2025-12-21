#pragma once
#include "CommandLine/LCommand.h"

namespace EngineRuntime
{
	class HelpCommand : public LCommand
	{
	public:
		~HelpCommand() override;
		const char* GetName() const override { return "help";}
		const char* GetDescription() const override;
		int Execute(const QStringList& args) override;
	};
}


