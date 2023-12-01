#pragma once

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "SDL.h"
#include "Renderable.h"

/**
 * @class Sprite
 *
 * Sprite is a derived class of Renderable and serves to render a single texture on screen
 */
class Sprite : public Renderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Sprite, Renderable);

protected:
	SDL_Texture* texture = nullptr;
	SDL_Rect sourceRect = { 0,0,0,0 };
	SDL_Rect targetRect = { 0,0,0,0 };

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
	 * @brief Updates the sprite class
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
	 * @brief Sprite constructor
	 *
	 */
	Sprite();

	/**
	 * @brief Sprite destructor
	 *
	 */
	~Sprite();

	/**
	 * @brief Setter for the texture area to render
	 *
	 * @param _rect A rect of four values describing the area of the texture to render
	 */
	void SetSourceRect(SDL_Rect _rect);

	/**
	 * @brief Initializes the sprite class
	 *
	 * @param _texture A pointer to an SDL texture for this class to render
	 */
	void SetNewTexture(SDL_Texture* _texture);


	/**
	 * @brief Loads the component and texture information from JSON
	 *
	 * @param document The json containing component information
	 */
	void Load(json::JSON& document) override;
	
};

#endif