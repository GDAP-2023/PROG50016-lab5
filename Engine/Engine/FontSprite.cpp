/*
* @FontSprite
*
* Allows the user to display text onto the SDL Window. They can control the text content,
* font used by providing a new asset to use, and the texts display color.
*/

#include "EngineCore.h"
#include "FontSprite.h"
#include "SDL_ttf.h";
#include "RenderSystem.h"
#include "Entity.h"

IMPLEMENT_DYNAMIC_CLASS(FontSprite);

FontSprite::FontSprite()
{

}

FontSprite::~FontSprite()
{

}

void FontSprite::Initialize()
{
	//PULL A DEFAULT FONT
	RegenerateOutput();
}

void FontSprite::Destroy()
{
	SDL_DestroyTexture(_output);
}

void FontSprite::Render()
{
	SDL_Point outputSizing;
	SDL_QueryTexture(_output, NULL, NULL, &outputSizing.x, &outputSizing.y);

	//_fontRect = { Entity::Instance().GetComponent("Transform").GetX(), Entity::Instance().GetComponent("Transform").GetY(), 
	//		outputSizing,x, outputSizing.y };
	//SDL_RenderCopy(&RenderSystem::Instance().GetRenderer(), _output, NULL, &_fontRect);
}

/*
* @SetText
*
* Takes a string for the display text and regenerates the font texture.
*/
void FontSprite::SetText(std::string text)
{
	_text = text;
	RegenerateOutput();
}

/*
* @SetFont
*
* Takes a TextureAsset for the new font and regenerates the font texture.
*/
void FontSprite::SetFont(TextureAsset* font)
{
	_font = font;
	RegenerateOutput();
}

/*
* @SetFontColor
*
* Takes RGB values along with an Alpha and regenerates the font texture.
*/
void FontSprite::SetFontColor(int r, int g, int b, int a)
{
	_fontColor.r = r;
	_fontColor.g = g;
	_fontColor.b = b;
	_fontColor.a = a;
	RegenerateOutput();
}

/*
* @RegenerateOutput
*
* Used by other methods to regenerate the SDL_Texture after things like text, font or color
* have changed.
*/
void FontSprite::RegenerateOutput()
{
	//SDL_Surface* textSurface = TTF_RenderText_Solid(TTF_OpenFont(_font.NAME, _font.SIZING), _text, _fontColor);
	//_output = SDL_CreateTextureFromSurface(&RenderSystem::Instance().GetRenderer(), textSurface);
	//SDL_FreeSurface(textSurface);
}