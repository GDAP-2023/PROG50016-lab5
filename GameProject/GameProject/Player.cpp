#include "GameCore.h"
#include "Player.h"
Player::Player(float x, float y, float speed)
	: posX(x), posY(y), speed(speed), health(100), score(0) {
}

Player::~Player() {
	// Cleanup if needed
}

void Player::update(const InputSystem& inputSystem) {
	// Keyboard movement with WASD and arrow keys
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			int joystickIndex = event.cdevice.which;
			SDL_GameController* gamepad = SDL_GameControllerOpen(joystickIndex);
			// Assign an ID to this gamepad, like the index or a unique identifier
			gamepadId = joystickIndex; // This is a simplification
		}
		if (inputSystem.isKeyPressed(SDLK_LEFT) || inputSystem.isKeyPressed(SDLK_a)) {
			moveLeft();
		}
		if (inputSystem.isKeyPressed(SDLK_RIGHT) || inputSystem.isKeyPressed(SDLK_d)) {
			moveRight();
		}
		if (inputSystem.isKeyPressed(SDLK_UP) || inputSystem.isKeyPressed(SDLK_w)) {
			moveUp();
		}
		if (inputSystem.isKeyPressed(SDLK_DOWN) || inputSystem.isKeyPressed(SDLK_s)) {
			moveDown();
		}

		// Gamepad movement
		if (inputSystem.isGamepadButtonPressed(gamepadId, SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
			inputSystem.getGamepadAxisState(gamepadId, SDL_CONTROLLER_AXIS_LEFTX) < -gamepadDeadzone) {
			moveLeft();
		}
		if (inputSystem.isGamepadButtonPressed(gamepadId, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ||
			inputSystem.getGamepadAxisState(gamepadId, SDL_CONTROLLER_AXIS_LEFTX) > gamepadDeadzone) {
			moveRight();
		}
		if (inputSystem.isGamepadButtonPressed(gamepadId, SDL_CONTROLLER_BUTTON_DPAD_UP) ||
			inputSystem.getGamepadAxisState(gamepadId, SDL_CONTROLLER_AXIS_LEFTY) < -gamepadDeadzone) {
			moveUp();
		}
		if (inputSystem.isGamepadButtonPressed(gamepadId, SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
			inputSystem.getGamepadAxisState(gamepadId, SDL_CONTROLLER_AXIS_LEFTY) > gamepadDeadzone) {
			moveDown();
		}

		updatePhysics();
		handleCollisions();
	}
}

void Player::render() {
	// Render the player using your graphics system
	// Example: drawPlayer(posX, posY); 
}

void Player::moveLeft() {
	posX -= speed;
}

void Player::moveRight() {
	posX += speed;
}

void Player::moveUp() {
	posY -= speed;
}

void Player::moveDown() {
	posY += speed;
}

float Player::getX() const {
	return posX;
}

float Player::getY() const {
	return posY;
}

void Player::setX(float x) {
	posX = x;
}

void Player::setY(float y) {
	posY = y;
}

void Player::handleCollisions() {
	// Collision handling logic
}

void Player::updatePhysics() {
	// Update player physics, like gravity
}