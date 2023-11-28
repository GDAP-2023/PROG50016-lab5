#pragma once

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "SDL.h"
#include "Renderable.h"

class Sprite : public Renderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Sprite, Renderable);

private:
	SDL_Texture* texture;
	SDL_Rect sourceRect;

	void Initialize();

	void Destroy();

	void Update();

	void Render() override;

public:
	void SetSourceRect(SDL_Rect _rect);

	void SetNewTexture(SDL_Texture* _texture);

protected:
	Sprite();
	~Sprite();
};

#endif