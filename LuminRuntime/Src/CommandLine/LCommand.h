#pragma once
#include <QStringList>

namespace EngineRuntime
{
	class LCommand
	{
	public:
		virtual ~LCommand() = default;
		// command name, eg: "new", "run"
		virtual const char* GetName() const = 0;
		// short description, -help output
		virtual const char* GetDescription() const = 0;
		// Execute
		virtual int Execute(const QStringList& args) = 0;
	};
}
