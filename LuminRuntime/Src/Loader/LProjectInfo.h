#pragma once
#include <QString>

namespace EngineRuntime
{
	struct LProjectInfo
	{
		QString projectName;
		QString projectPath;
		QString gameModuleName;
		QString gameDllPath;
		QString contentDir;

		bool IsValid() const
		{
			return !projectName.isEmpty()
				&& !gameDllPath.isEmpty();
		}
	};
}
