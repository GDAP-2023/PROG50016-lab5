#include "GameCore.h"

int main()
{
	Engine::Instance().Initialize();
	Engine::Instance().GameLoop();
	Engine::Instance().Destroy();
}
