#include "EngineCore.h"
#include "Engine.h"
#include "EngineTime.h"
#include "RenderSystem.h"
#include "SceneManager.h"
#include "Entity.h"
#include "InputSystem.h"

#include <thread>

#include "AssetManager.h"
#include "AudioSystem.h"
#include "Component.h"

Engine* Engine::instance = nullptr;

extern void Engine_Register();

void Engine::Initialize()
{
	Engine_Register();

	// Load the managers
	AssetManager::Get().Load("../Assets/AssetManager.json");
	SceneManager::Get().Load();

	// Initialize the managers
	AssetManager::Get().Initialize();
	RenderSystem::Get().Initialize();
	AudioSystem::Get().Initialize();

	SceneManager::Get().Initialize();

	InputSystem::Get().registerQuitEventHandler([this] {isRunning = false; });
}

void Engine::Destroy()
{
	Time::Instance().Destroy();
	AssetManager::Get().Destroy();
	AudioSystem::Get().Destroy();
	RenderSystem::Get().Destroy();
	delete instance;
	instance = nullptr;
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
		RenderSystem::Get().Update();

		// --------------------- Post-update Phase ---------------------
		SceneManager::Get().PostUpdate();


		/*	if (Time::Instance().TotalTime() > 5.0f)
			{
				break;
			}*/


			// --------------------- Input Phase ---------------------
		InputSystem::Get().Update();

	/*	if (Time::Instance().TotalTime() > 5.0f)
		{
			break;
		}*/

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				InputSystem::Get().handleQuitEvent();
			}
		}


	}
}
