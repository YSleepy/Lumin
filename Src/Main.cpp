#include <thread>

#include "Engine/LApp.h"
#include "Example/EGameInstance.h"
#include "Engine/LEngine.h"

int main(int argc, char *argv[])
{
	Lumin::LApp app(argc, argv);

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
