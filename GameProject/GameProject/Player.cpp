#include "GameCore.h"
#include "Player.h"

#include <EngineTime.h>
#include <Entity.cpp>



void Player::Update(const InputSystem& inputSystem) {
	 Transform& player = ownerEntity->GetTransform();
	Vec2 dir = Vec2::Zero;
	InputSystem& input = InputSystem::Instance();

	if (input.isKeyPressed(SDLK_LEFT) || input.isKeyPressed(SDLK_a) || input.isGamepadButtonPressed(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
		dir.x -= 1;
	}
	if (input.isKeyPressed(SDLK_RIGHT) || input.isKeyPressed(SDLK_d) || input.isGamepadButtonPressed(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
		dir.x += 1;
	}
	if (input.isKeyPressed(SDLK_UP) || input.isKeyPressed(SDLK_w) || input.isGamepadButtonPressed(0, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
		dir.y -= 1;
	}
	if (input.isKeyPressed(SDLK_DOWN) || input.isKeyPressed(SDLK_s) || input.isGamepadButtonPressed(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
		dir.y += 1;
	}

	if (dir == Vec2::Zero) {
		dir.x = input.getGamepadAxisState(0, SDL_CONTROLLER_AXIS_LEFTX);
		dir.y = input.getGamepadAxisState(0, SDL_CONTROLLER_AXIS_LEFTY);
	}

	if (dir != Vec2::Zero) {
		dir.Normalize();
	}

	// player.pos += dir * speed * Time::Instance().DeltaTime();;

}
