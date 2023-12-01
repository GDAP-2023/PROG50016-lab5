#include "EngineCore.h"
#include "Engine.h"
#include "EngineTime.h"
#include "RenderSystem.h"
#include "SceneManager.h"
#include "Entity.h"
#include "InputSystem.h"

#include <thread>

#include "Component.h"

Engine* Engine::instance = nullptr;

extern void Engine_Register();

void Engine::Initialize()
{
	Engine_Register();

	// Load the managers
	SceneManager::Get().Load();

	// Initialize the managers
	RenderSystem::Instance().Initialize();
	SceneManager::Get().Initialize();
	InputSystem::Instance().setupQuitHandler(*this);
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
	while (isRunning)
	{
		Time::Instance().Update();

		// --------------------- Pre-update Phase ---------------------
		SceneManager::Get().PreUpdate();

		// --------------------- Update Phase ---------------------
		SceneManager::Get().Update();
		RenderSystem::Instance().Update();

		// --------------------- Post-update Phase ---------------------
		SceneManager::Get().PostUpdate();

	/*	if (Time::Instance().TotalTime() > 5.0f)
		{
			break;
		}*/

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				InputSystem::Instance().handleQuitEvent();
			}
		}

	}
}
