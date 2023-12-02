#include "EngineCore.h"
#include "AnimatedSprite.h"
#include "RenderSystem.h"
#include "EngineTime.h"
#include "Entity.h"

IMPLEMENT_DYNAMIC_CLASS(AnimatedSprite);

AnimatedSprite::AnimatedSprite() {
	
}

AnimatedSprite::~AnimatedSprite() {

}

void AnimatedSprite::Initialize() {

}

void AnimatedSprite::Destroy() {

}

void AnimatedSprite::Update() {
	Transform t = ownerEntity->GetTransform();
	targetRect = {
		(int)(t.position.x - spriteWidth * .5f),
		(int)(t.position.y - spriteHeight * .5f),
		spriteWidth,
		spriteHeight
	};
	if (t.position.x < 0) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	if (t.position.y < 0) {
		flip = SDL_FLIP_VERTICAL;
	}

	if (!running) return;
	frameCounter += Time::Instance().DeltaTime();

	spriteRect.x = spriteWidth * (currentFrame % spriteSheetColumns);
	spriteRect.y = spriteHeight * (int)(currentFrame / spriteSheetColumns);
	if (currentFrame == totalFrames) {
		if (loop) {
			currentFrame = 0;
		}
		else {
			running = false;
		}
	}
	if (frameCounter >= frameDelay) {
		frameCounter = 0;
		currentFrame++;
	}
}

void AnimatedSprite::Render() {
	SDL_SetTextureColorMod(texture, _filterColor.r, _filterColor.g, _filterColor.b);
	SDL_RenderCopyEx(
		&RenderSystem::Instance().GetRenderer(),
		texture,
		&spriteRect,
		&targetRect,
		ownerEntity->GetTransform().rotation,
		NULL,
		flip
	);
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void AnimatedSprite::SetSpriteSheet(int rows, int cols, int _totalFrames) {
	spriteSheetRows = rows;
	spriteSheetColumns = cols;
	totalFrames = _totalFrames;

	spriteWidth = sourceRect.w / cols;
	spriteHeight = sourceRect.h / rows;

	spriteRect = {
		sourceRect.x,
		sourceRect.y,
		spriteWidth,
		spriteHeight
	};

	targetRect = {
		(int)(ownerEntity->GetTransform().position.x - spriteWidth * .5f),
		(int)(ownerEntity->GetTransform().position.y - spriteHeight * .5f),
		spriteWidth,
		spriteHeight
	};
}

void AnimatedSprite::Restart() {
	currentFrame = defaultFrameNumber;
}

void AnimatedSprite::Stop() {
	currentFrame = defaultFrameNumber;
	running = false;
}

void AnimatedSprite::Play() {
	running = true;
}

void AnimatedSprite::Pause() {
	running = false;
}