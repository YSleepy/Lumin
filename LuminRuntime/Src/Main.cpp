#include <thread>
#include <filesystem>
#include <QtGui/QSurfaceFormat>

#include "Engine/LApp.h"
#include "Example/EGameInstance.h"
#include "Engine/LEngine.h"
#include "Log/LLog.h"


int main(int argc, char* argv[])
{
	Lumin::LApp app(argc, argv);
	Lumin::InitLog();
	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setVersion(3, 3);  // 设置 OpenGL 版本
	format.setProfile(QSurfaceFormat::CoreProfile);  // 核心模式
	QSurfaceFormat::setDefaultFormat(format);

	qDebug() << "Main Thread";
	Lumin::LEngine& engine = Lumin::LEngine::GetInstance();
	EGameInstance* gameInstance = new EGameInstance();
	engine.SetGameInstance(gameInstance);
	Lumin::LEngineConfig engineConfig{
		{
			1080,
			960
		}
	};
	if (engine.Init(engineConfig))
	{
		std::thread engineThread(
			[&engine]()
			{
				engine.Run();//Run内有游戏主循环
			}
		);
		app.exec();
		engineThread.join();
		engine.Destroy();
	}
	return 0;
}
