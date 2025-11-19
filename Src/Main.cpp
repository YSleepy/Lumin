#include "Example/EGameInstance.h"
#include "Engine/LEngine.h"

int main()
{
	Lumin::LEngine engine;
	EGameInstance* gameInstance = new EGameInstance();
	engine.SetGameInstance(gameInstance);
	if (engine.Init())
	{
		engine.Run();
	}
	engine.Destroy();
	return 0;
}
