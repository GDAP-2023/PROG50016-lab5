#include "EngineCore.h"
#include "InputSystem.h"

InputSystem* InputSystem::instance = nullptr;


InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::Initialize()
{
	// Initialize the state of the input system
// Initialize keyStates and mouseButtonStates
// Initialize keyEventHandlers and mouseEventHandlers
	for (int i = 0; i < 256; i++) {
		keyStates[i] = false;
	}
	for (int i = 0; i < 5; i++) {
		mouseButtonStates[i] = false;
	}
}

void InputSystem::update()
{

	// Update the state of the input system every frame
	   // Handle events
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (!keyStates[event.key.keysym.sym]) { // Only if the key was previously up
				keyStates[event.key.keysym.sym] = true;
				triggerKeyEvent(event.key.keysym.sym, true);
			}
			break;
		case SDL_KEYUP:
			if (keyStates[event.key.keysym.sym]) { // Only if the key was previously down
				keyStates[event.key.keysym.sym] = false;
				triggerKeyEvent(event.key.keysym.sym, false);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			mouseButtonStates[event.button.button] = (event.type == SDL_MOUSEBUTTONDOWN);
			triggerMouseEvent(event.button.button, event.type == SDL_MOUSEBUTTONDOWN);
			break;
		case SDL_QUIT:

			if (quitEventHandler) {
				quitEventHandler();
			}

			break;
		}
	}
}


void InputSystem::triggerKeyEvent(SDL_Keycode key, bool pressed) {
	auto it = pressed ? keyPressHandlers.find(key) : keyReleaseHandlers.find(key);
	auto end = pressed ? keyPressHandlers.end() : keyReleaseHandlers.end();

	if (it != end) {
		it->second();
	}
}

void InputSystem::triggerMouseEvent(Uint8 button, bool pressed) {
	auto it = pressed ? mousePressHandlers.find(button) : mouseReleaseHandlers.find(button);
	auto end = pressed ? mousePressHandlers.end() : mouseReleaseHandlers.end();

	if (it != end) {
		it->second();
	}
}
	

	bool InputSystem::areKeysPressed(const std::vector<SDL_Keycode>&keys) const
	{
		for (auto key : keys) {
			if (!isKeyPressed(key))
				return false;
		}
		return true;
	}
	bool InputSystem::isKeyPressed(SDL_Keycode key) const {
		return keyStates[key];
	}

	bool InputSystem::isMouseButtonPressed(Uint8 button) const {
		return mouseButtonStates[button];
	}


	void InputSystem::registerKeyEventHandler(SDL_Keycode key, bool onPress, std::function<void()> handler) {
		if (onPress) {
			keyPressHandlers[key] = handler;
		}
		else {
			keyReleaseHandlers[key] = handler;
		}
	}

	void InputSystem::registerMouseEventHandler(Uint8 button, bool onPress, std::function<void()> handler) {
		if (onPress) {
			mousePressHandlers[button] = handler;
		}
		else {
			mouseReleaseHandlers[button] = handler;
		}
	}

	void InputSystem::registerQuitEventHandler(std::function<void()> handler) {
		quitEventHandler = handler;
	}

