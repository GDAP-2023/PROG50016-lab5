#pragma once

#ifndef _ANIMATED_SPRITE_H_
#define _ANIMATED_SPRITE_H_

#include "Sprite.h"

/**
 * @class AnimatedSprite
 *
 * AnimatedSprite is a derived class of Sprite that renders an animation using a spritesheet
 */
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

	int currentFrame = 0;
	float frameDelay = 0.1f;

private:
	float frameCounter = 0;
	bool running = true;
	bool loop = true;

	/**
	 * @brief Initializes any variables as needed
	 *
	 */
	void Initialize();

	/**
	 * @brief Cleans up any memory and pointers as needed
	 *
	 */
	void Destroy();

	/**
	 * @brief Updates the animation frame to render based off of game time
	 *
	 */
	void Update();

	/**
	 * @brief Copies the sprite onto a renderer to be displayed for that frame
	 *
	 */
	void Render() override;

public:
	/**
	 * @brief AnimatedSprite constructor
	 *
	 */
	AnimatedSprite();

	/**
	 * @brief AnimatedSprite destructor
	 *
	 */
	~AnimatedSprite();

	/**
	 * @brief Setter for how to parse the spritesheet
	 *
	 * @param rows How many rows from the spritesheet to parse
	 * @param cols How many columns from the spritesheet to parse
	 * @param frames How many frames/sprites make up this animation
	 */
	void SetSpriteSheet(int rows, int cols, int frames);

	/**
	 * @brief Restart the current animation frame to 0
	 */
	void Restart();

	/**
	 * @brief Stops the animation, reverting to the default frame
	 */
	void Stop();

	/**
	 * @brief Plays the animation from the current frame
	 */
	void Play();

	/**
	 * @brief Pauses the animation on the current frame
	 */
	void Pause();
};

#endif