#include "GameCore.h"

extern void Game_Register();

int main()
{
	Game_Register();

	Engine::Get().Initialize();
	Engine::Get().GameLoop();
	Engine::Get().Destroy();

	return 0;
}
