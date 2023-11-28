#pragma once

#ifndef _ANIMATED_SPRITE_H_
#define _ANIMATED_SPRITE_H_

#include "Sprite.h"
class AnimatedSprite : public Sprite
{
	DECLARE_DYNAMIC_DERIVED_CLASS(AnimatedSprite, Sprite);
public:
	int spriteSheetRows = 0;
	int spriteSheetColumn = 0;
	int spriteCount = 0;
	int defaultFrameNumber = 0;
	float animationDelay = 0.1f;

private:
	int frameCount = 0;
	bool running = true;
	bool loop = false;

	void Initialize();

	void Destroy();

	void Update();

	void Render() override;

protected:
	AnimatedSprite();
	~AnimatedSprite();

	void SetSpriteSheet(int rows, int cols, int spriteCount);

	void Restart();

	void Stop();

	void Play();

	void Pause();
};

#endif