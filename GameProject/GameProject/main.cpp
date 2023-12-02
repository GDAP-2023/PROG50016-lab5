#include "GameCore.h"

extern void Game_Register();

int main()
{
	Game_Register();

	Engine::Instance().Initialize();
	Engine::Instance().GameLoop();
	Engine::Instance().Destroy();

	return 0;
}
