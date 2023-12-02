#define SDL_MAIN_HANDLED
#include "GameCore.h"

void Engine_Register();
void Game_Register();

int main()
{
	Engine_Register();
	Game_Register();

	Engine::Instance().Initialize();
	Engine::Instance().GameLoop();
	Engine::Instance().Destroy();

	return 0;
}
