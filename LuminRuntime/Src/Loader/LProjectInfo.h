#pragma once
#include <QString>

namespace EngineRuntime
{
	struct LProjectInfo
	{
		QString projectName;
		QString gameModuleName;
		QString gameDllPath;
		QString contentDir;
		QString startupMap;

		bool IsValid() const
		{
			return !projectName.isEmpty()
				&& !gameDllPath.isEmpty();
		}
	};
}
