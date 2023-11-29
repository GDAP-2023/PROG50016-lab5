#pragma once

#ifndef _ANIMATED_SPRITE_H_
#define _ANIMATED_SPRITE_H_

#include "Sprite.h"
class AnimatedSprite : public Sprite {
	DECLARE_DYNAMIC_DERIVED_CLASS(AnimatedSprite, Sprite);
public:
	SDL_Rect spriteRect = { 0,0,0,0 };
	int spriteSheetRows = 0;
	int spriteSheetColumns = 0;

	int spriteWidth = 0;
	int spriteHeight = 0;

	int totalFrames = 0;
	int defaultFrameNumber = 0;
	float animationDelay = 0.1f;

private:
	int currentFrame = 0;
	bool running = true;
	bool loop = false;

	void Initialize();

	void Destroy();

	void Update();

	void Render() override;

protected:
	AnimatedSprite();
	~AnimatedSprite();

	void SetSpriteSheet(int rows, int cols, int frames);

	void Restart();

	void Stop();

	void Play();

	void Pause();
};

#endif