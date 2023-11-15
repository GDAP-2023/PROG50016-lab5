#include "EngineCore.h"
#include "Engine.h"
#include "EngineTime.h"
#include "RenderSystem.h"
#include "Entity.h"

#include <thread>

#include "Component.h"

Engine* Engine::instance = nullptr;

extern void Engine_Register();

void Engine::Initialize()
{
	Engine_Register();

	RenderSystem::Instance().Initialize();
}

void Engine::Destroy()
{
	Time::Instance().Destroy();

	if (instance == nullptr)
	{
		delete instance;
	}
}

void Engine::GameLoop()
{
	while (true)
	{
		Time::Instance().Update();

		RenderSystem::Instance().Update();

		if (Time::Instance().TotalTime() > 5.0f)
		{
			break;
		}
	}
}
