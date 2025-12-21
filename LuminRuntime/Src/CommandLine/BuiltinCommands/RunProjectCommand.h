#pragma once
#include "CommandLine/LCommand.h"

namespace EngineRuntime
{
	class RunProjectCommand : public LCommand
	{
	public:
		const char* GetName() const override { return "run"; }
		const char* GetDescription() const override;

		int Execute(const QStringList& args) override;
	};
}
