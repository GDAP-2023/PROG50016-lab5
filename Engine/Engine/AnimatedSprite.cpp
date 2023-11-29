#include "EngineCore.h"
#include "AnimatedSprite.h"
#include "RenderSystem.h"

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
	if (!running) return;
	
	spriteRect.x += spriteWidth * (currentFrame % spriteSheetColumns);
	spriteRect.y += spriteHeight * (int)(currentFrame / spriteSheetColumns);
	if (currentFrame == totalFrames) {
		if (loop) {
			currentFrame = 0;
		}
		else {
			running = false;
		}
	}
	currentFrame++;
}

void AnimatedSprite::Render() {
	SDL_SetTextureColorMod(texture, _filterColor.r, _filterColor.g, _filterColor.b);
	double angle = 0;
	SDL_RenderCopyEx(&RenderSystem::Instance().GetRenderer(), texture, &sourceRect, &targetRect, angle, NULL, SDL_FLIP_NONE);
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