#pragma once

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "SDL.h"
#include "Renderable.h"

class Sprite : public Renderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Sprite, Renderable);

protected:
	SDL_Texture* texture;
	SDL_Rect sourceRect = { 0,0,0,0 };
	SDL_Rect targetRect = { 0,0,0,0 };

	void Initialize();

	void Destroy();

	void Update();

	void Render() override;

public:
	Sprite();
	~Sprite();

	void SetSourceRect(SDL_Rect _rect);

	void SetNewTexture(SDL_Texture* _texture);
	
};

#endif