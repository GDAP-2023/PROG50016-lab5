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
			if (!mouseButtonStates[event.button.button]) { // Only if the button was previously up
				mouseButtonStates[event.button.button] = true;
				triggerMouseEvent(event.button.button, true);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (mouseButtonStates[event.button.button]) { // Only if the button was previously down
				mouseButtonStates[event.button.button] = false;
				triggerMouseEvent(event.button.button, false);
			}
			if (event.type == SDL_CONTROLLERDEVICEADDED) {
				int joystickIndex = event.cdevice.which;
				SDL_GameController* gamepad = SDL_GameControllerOpen(joystickIndex);
				// Assign an ID to this gamepad, like the index or a unique identifier
				gamepadId = joystickIndex;

			}
		case SDL_CONTROLLERBUTTONDOWN:
			handleGamepadButton(event.cbutton.which, static_cast<SDL_GameControllerButton>(event.cbutton.button), true);
			break;
		case SDL_CONTROLLERBUTTONUP:
			handleGamepadButton(event.cbutton.which, static_cast<SDL_GameControllerButton>(event.cbutton.button), false);
			break;
		case SDL_CONTROLLERAXISMOTION:
			handleGamepadAxis(event.caxis.which, static_cast<SDL_GameControllerAxis>(event.caxis.axis), event.caxis.value);
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
	void InputSystem::handleGamepadConnection(int joystickIndex) {
		SDL_GameController* gamepad = SDL_GameControllerOpen(joystickIndex);
		if (gamepad) {
			InputSystem::gamepadMap[joystickIndex] = gamepad;
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

	void InputSystem::initializeGamepads() {
		int numJoysticks = SDL_NumJoysticks();
		for (int i = 0; i < numJoysticks; ++i) {
			if (SDL_IsGameController(i)) {
				SDL_GameController* controller = SDL_GameControllerOpen(i);
				if (controller) {
					// Store the controller in a container if needed
				}
				else {
					SDL_Log("Could not open gamecontroller %i: %s", i, SDL_GetError());
				}
			}
		}
	}
	void InputSystem::handleGamepadButton(SDL_JoystickID joystickID, SDL_GameControllerButton button, bool pressed) {
		// You might want to keep track of the state of each button for each gamepad
		gamepadButtonStates[joystickID][button] = pressed;

		// Trigger gamepad button event callbacks if any
		if (gamepadButtonEventHandlers.find(joystickID) != gamepadButtonEventHandlers.end() &&
			gamepadButtonEventHandlers[joystickID].find(button) != gamepadButtonEventHandlers[joystickID].end()) {
			gamepadButtonEventHandlers[joystickID][button](pressed);
		}

		// Other game logic related to gamepad button press/release...
	}

	void InputSystem::registerGamepadButtonEventHandler(SDL_JoystickID joystickID, SDL_GameControllerButton button, std::function<void(bool)> handler)
	{

		gamepadButtonEventHandlers[joystickID][button] = handler;
	}

	bool InputSystem::isGamepadButtonPressed(SDL_JoystickID joystickID, SDL_GameControllerButton button) const {
		auto joystickIt = gamepadButtonStates.find(joystickID);
		if (joystickIt != gamepadButtonStates.end()) {
			auto buttonIt = joystickIt->second.find(button);
			if (buttonIt != joystickIt->second.end()) {
				return buttonIt->second;
			}
		}
		return false; // Default to not pressed if not found
	}

	void InputSystem::handleGamepadAxis(SDL_JoystickID joystickID, SDL_GameControllerAxis axis, Sint16 value) {
		// Update the state of the axis
		gamepadAxisStates[joystickID][axis] = value;

		// Perform any actions based on the axis movement.
		// This might involve updating game logic, character movement, camera control, etc.
		// For example:
		if (axis == SDL_CONTROLLER_AXIS_LEFTX || axis == SDL_CONTROLLER_AXIS_LEFTY) {
			// Handle left analog stick movement
	
			


		}
		else if (axis == SDL_CONTROLLER_AXIS_RIGHTX || axis == SDL_CONTROLLER_AXIS_RIGHTY) {

			// Handle right analog stick movement


		}

		// You can also call specific callbacks or notify observers if your design uses them


	}

	Sint16 InputSystem::getGamepadAxisState(SDL_JoystickID joystickID, SDL_GameControllerAxis axis) const {
    auto joystickIt = gamepadAxisStates.find(joystickID);
    if (joystickIt != gamepadAxisStates.end()) {
        auto axisIt = joystickIt->second.find(axis);
        if (axisIt != joystickIt->second.end()) {
            return axisIt->second;

        }

    }

    return 0; // Default state if not found
}
	void InputSystem::registerQuitEventHandler(std::function<void()> handler) {
		quitEventHandler = handler;

	}

