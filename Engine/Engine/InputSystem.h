#pragma once
#include "Engine.h"
#include <SDL_keycode.h>
#include <SDL.h>

class InputSystem
{


public:
	// Singleton pattern: 

	friend class Engine;

	static InputSystem& Instance() {
	
		if (instance == nullptr)
		{
			instance = new InputSystem();
			instance->Initialize();
		}
		return *instance;
	}
	InputSystem();
	~InputSystem();
	void Initialize();
	void update();
	bool isKeyPressed(SDL_Keycode key) const;
	bool areKeysPressed(const std::vector<SDL_Keycode>& keys) const;
	bool isMouseButtonPressed(Uint8 button) const;
	void handleKeyPress(SDL_Keycode key);
	void handleKeyRelease(SDL_Keycode key);
	void handleMouseButtonPress(Uint8 button);
	void handleMouseButtonRelease(Uint8 button);

	void registerKeyEventHandler(SDL_Keycode key, std::function<void()> handler);
	void registerMouseEventHandler(Uint8 button, std::function<void()> handler);

private:
	std::map<SDL_Keycode, bool> keyStates;
	std::map<Uint8, bool> mouseButtonStates;
	InputSystem(const& inputSystem);
	InputSystem operator = (const& InputSystem);
	static InputSystem* instance;
	std::map<SDL_Keycode, std::function<void()>> keyEventHandlers; // Caching function pointers for key events
	std::map<Uint8, std::function<void()>> mouseEventHandlers; // Caching function pointers for mouse events

};


