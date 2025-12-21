#include "LGameBootstrap.h"
#include "Example/EGameModule.h"
#include "LProjectLoader.h"
#include <QDebug>

namespace EngineRuntime
{
	Lumin::LGameModuleBase* LGameBootstrap::SelectGameModule(LProjectLoader* projectLoader)
	{
		if (projectLoader && projectLoader->HasProject())
		{
			qDebug() << "Using external game module";
			return projectLoader->CreateGameModule();
		}

		qDebug() << "Using built-in default game module";
		static DefaultGameMode::EGameModule defaultModule;
		return &defaultModule;
	}
}
