#pragma once
#ifndef _FONT_SPRITE_
#define _FONT_SPRITE_

#include <iostream>
#include "Renderable.h"
#include "SDL.h"

class TextureAsset;

class FontSprite : public Renderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(FontSprite, Renderable);

	std::string _text = "DEFAULT TEXT";

	TextureAsset* _font = nullptr;

	SDL_Rect _fontRect = { 0,0,250,250 };

	SDL_Texture* _output = nullptr;

	SDL_Color _fontColor = { 255,255,255,255 };

	void RegenerateOutput();

protected:

	FontSprite();

	~FontSprite();

	void Initialize();

	void Update();

	void Destroy();

	void Render() override;

public:

	void SetText(std::string text);

	void SetFont(TextureAsset* font);

	void SetFontColor(int r, int g, int b, int a);
};

#endif
