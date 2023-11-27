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
        case SDL_KEYDOWN:  // If a key is pressed
            if (!event.key.repeat) { // To ignore key repeat events
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    // Handle 'W' key press
                    handleKeyPress(SDLK_w);
                    break;
                case SDLK_s:
                    // Handle 'S' key press
                    handleKeyPress(SDLK_s);
                    break;
                case SDLK_a:
                    // Handle 'A' key press
                    handleKeyPress(SDLK_a);
                    break;
                case SDLK_d:
                    // Handle 'D' key press
                    handleKeyPress(SDLK_d);
                    break;
               
                    // Update keyStates and call function pointer if it exists
                    keyStates[event.key.keysym.sym] = (event.type == SDL_KEYDOWN);
                    if (keyEventHandlers.find(event.key.keysym.sym) != keyEventHandlers.end()) {
                        keyEventHandlers[event.key.keysym.sym]();
                    }
                    break;
                    // ... handle other events
                }
            }

        case SDL_KEYUP:

            switch (event.key.keysym.sym) {
            case SDLK_w:
                // Handle 'W' key release
                handleKeyRelease(SDLK_w);
                break;
            case SDLK_s:
                // Handle 'S' key release
                handleKeyRelease(SDLK_s);
                break;
            case SDLK_a:
                // Handle 'A' key release
                handleKeyRelease(SDLK_a);
                break;
            case SDLK_d:
                // Handle 'D' key release
                handleKeyRelease(SDLK_d);
                break;
                // ... handle other keys ...
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            // Update mouseButtonStates and call function pointer if it exists
            mouseButtonStates[event.button.button] = (event.type == SDL_MOUSEBUTTONDOWN);
            if (mouseEventHandlers.find(event.button.button) != mouseEventHandlers.end()) {
                mouseEventHandlers[event.button.button]();
            }
            break;
        }
    }
}

bool InputSystem::isKeyPressed(SDL_Keycode key) const
{
    auto it = keyStates.find(key);
    return it != keyStates.end() && it->second;
}

bool InputSystem::areKeysPressed(const std::vector<SDL_Keycode>& keys) const
{
    for (auto key : keys) {
        if (!isKeyPressed(key))
            return false;
    }
    return true;
}

bool InputSystem::isMouseButtonPressed(Uint8 button) const
{
    auto it = mouseButtonStates.find(button);
    return it != mouseButtonStates.end() && it->second;
}

void InputSystem::handleKeyPress(SDL_Keycode key)
{
	// Update keyStates and call function pointer if it exists
	keyStates[key] = true;

    Player* player = Engine::Instance()->GetPlayer();

    switch (key) {
    case SDLK_w:
        player->moveForward();
        break;
    case SDLK_s:
        player->moveBackward();
        break;
    case SDLK_a:
        player->strafeLeft();
        break;
    case SDLK_d:
        player->strafeRight();
        break;
        // ... other keys ...
    }


    if (keyEventHandlers.find(key) != keyEventHandlers.end()) {
		keyEventHandlers[key]();
	}
}

void InputSystem::handleKeyRelease(SDL_Keycode key)
{
	// Update keyStates and call function pointer if it exists
	keyStates[key] = false;

    Player* player = Engine::Instance()->GetPlayer();

    switch (key) {
    case SDLK_w:
        player->stopForward();
        break;
    case SDLK_s:
        player->stopBackward();
        break;
    case SDLK_a:
        player->stopStrafeLeft();
        break;
    case SDLK_d:
        player->stopStrafeRight();
        break;
        // ... other keys ...
    }
    if (keyEventHandlers.find(key) != keyEventHandlers.end()) {
		keyEventHandlers[key]();
	}
}

void InputSystem::handleMouseButtonPress(Uint8 button)
{
	// Update mouseButtonStates and call function pointer if it exists
	mouseButtonStates[button] = true;
    if (mouseEventHandlers.find(button) != mouseEventHandlers.end()) {
		mouseEventHandlers[button]();
	}
}

void InputSystem::handleMouseButtonRelease(Uint8 button)
{

    // Update mouseButtonStates and call function pointer if it exists
    mouseButtonStates[button] = false;
    if (mouseEventHandlers.find(button) != mouseEventHandlers.end()) {
		mouseEventHandlers[button]();
	}


}

void InputSystem::registerKeyEventHandler(SDL_Keycode key, std::function<void()> handler)
{

	keyEventHandlers[key] = handler; 


}

void InputSystem::registerMouseEventHandler(Uint8 button, std::function<void()> handler)
{

    mouseEventHandlers[button] = handler; 
}
