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
#include "FontAsset.h"
#include "AssetManager.h"

IMPLEMENT_DYNAMIC_CLASS(FontSprite);

FontSprite::FontSprite() : Renderable()
{

}

FontSprite::~FontSprite()
{

}

/*
* @Initialize
*
* There is no default font. You will see nothing until you provide a font to the FontSprite
*/
void FontSprite::Initialize()
{
	RegenerateOutput();
}

void FontSprite::Update()
{
	Transform t = ownerEntity->GetTransform();

	_fontRect = {
		(int)ownerEntity->GetTransform().position.x,
		(int)ownerEntity->GetTransform().position.y,
			(int)(outputSizing.x * ownerEntity->GetTransform().scale.x), 
			(int)(outputSizing.y * ownerEntity->GetTransform().scale.y)
	};

	flip = SDL_FLIP_NONE;
	if (t.scale.x < 0) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	if (t.scale.y < 0) {
		flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL);
	}
}

void FontSprite::Destroy()
{
	SDL_DestroyTexture(_output);
}

void FontSprite::Render()
{
	if (_output == NULL)
	{
		SDL_QueryTexture(_output, NULL, NULL, &outputSizing.x, &outputSizing.y);

		_fontRect = { (int)ownerEntity->GetTransform().position.x, (int)ownerEntity->GetTransform().position.y,
			(int)(outputSizing.x * ownerEntity->GetTransform().scale.x), (int)(outputSizing.y * ownerEntity->GetTransform().scale.y) };

		SDL_RenderCopyEx(
			&RenderSystem::Instance().GetRenderer(), 
			_output, NULL, 
			&_fontRect,
			ownerEntity->GetTransform().rotation,
			NULL,
			flip
		);
	}
}

void FontSprite::Save(json::JSON& document)
{
	document["Text"] = _text;

	json::JSON subObject = json::JSON::Object();
	subObject["R"] = _fontColor.r;
	subObject["G"] = _fontColor.g;
	subObject["B"] = _fontColor.b;
	subObject["A"] = _fontColor.a;

	document["FontColor"] = subObject;

	document["Font"] = _font->Getguid();
}

void FontSprite::Load(json::JSON& document)
{
	if (document.hasKey("Text"))
	{
		_text = document["Text"].ToString();
	}

	if (document.hasKey("FontColor"))
	{
		json::JSON subObject = document["FontColor"];
		_fontColor.r = subObject["R"].ToInt();
		_fontColor.g = subObject["G"].ToInt();
		_fontColor.b = subObject["B"].ToInt();
		_fontColor.a = subObject["A"].ToInt();
	}

	std::string guid = document["Font"].ToString();

	_font = (FontAsset*)AssetManager::Get().GetAsset(guid);

	RegenerateOutput();
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
void FontSprite::SetFont(FontAsset* font)
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
	if (_font == NULL)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid((*_font).GetFont(), _text.c_str(), _fontColor);
		_output = SDL_CreateTextureFromSurface(&RenderSystem::Instance().GetRenderer(), textSurface);
		SDL_FreeSurface(textSurface);
	}
}