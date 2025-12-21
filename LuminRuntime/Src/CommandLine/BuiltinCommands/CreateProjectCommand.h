#pragma once
#include "CommandLine/LCommand.h"

namespace EngineRuntime
{
	class CreateProjectCommand : public LCommand
	{
	public:
		const char* GetName() const override { return "new"; }
		const char* GetDescription() const override;

		int Execute(const QStringList& args) override;
	};
}
