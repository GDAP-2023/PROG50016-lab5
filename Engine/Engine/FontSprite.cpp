/*
* @FontSprite
*
* Allows the user to display text onto the SDL Window. They can control the text content,
* font used by providing a new asset to use, and the texts display color.
*/

#include "EngineCore.h"
#include "FontSprite.h"

#include <utility>
#include "SDL_ttf.h"
#include "RenderSystem.h"
#include "Entity.h"
#include "FontAsset.h"
#include "AssetManager.h"

IMPLEMENT_DYNAMIC_CLASS(FontSprite);

/*
* @Initialize
*
* There is no default font. You will see nothing until you provide a font to the FontSprite
*/
void FontSprite::Initialize()
{
    Renderable::Initialize();
    RegenerateOutput();
}

void FontSprite::Update()
{
    if (_output == nullptr)
    {
        return;
    }
    SDL_QueryTexture(_output, nullptr, nullptr, &outputSizing.x, &outputSizing.y);

    const Transform& transform = ownerEntity->GetTransform();

    _fontRect = { static_cast<int>(transform.position.x), static_cast<int>(transform.position.y),
        (outputSizing.x * static_cast<int>(transform.scale.x)), (outputSizing.y * static_cast<int>(transform.scale.y)) };

    flip = static_cast<SDL_RendererFlip>((transform.scale.x < 0) | ((transform.scale.y < 0) << 1));
}

void FontSprite::Destroy()
{
    SDL_DestroyTexture(_output);
    Renderable::Destroy();
}

void FontSprite::Render()
{
    if (_output == nullptr)
    {
        return;
    }

    const Transform& transform = ownerEntity->GetTransform();

    SDL_RenderCopyEx(
        &RenderSystem::Instance().GetRenderer(),
        _output,
        nullptr,
        &_fontRect,
        (double)transform.rotation,
        nullptr,
        flip
    );
}

void FontSprite::Save(json::JSON& document) const
{
    document["Text"] = _text;

    json::JSON subObject = json::JSON::Object();
    subObject["R"] = _fontColor.r;
    subObject["G"] = _fontColor.g;
    subObject["B"] = _fontColor.b;
    subObject["A"] = _fontColor.a;

    document["FontColor"] = subObject;

    document["Font"] = _font->GetGuid();
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
        _fontColor.r = static_cast<Uint8>(subObject["R"].ToInt());
        _fontColor.g = static_cast<Uint8>(subObject["G"].ToInt());
        _fontColor.b = static_cast<Uint8>(subObject["B"].ToInt());
        _fontColor.a = static_cast<Uint8>(subObject["A"].ToInt());
    }

    std::string guid = document["Font"].ToString();

    _font = dynamic_cast<FontAsset*>(AssetManager::Get().GetAsset(guid));

    RegenerateOutput();
}

/*
* @SetText
*
* Takes a string for the display text and regenerates the font texture.
*/
void FontSprite::SetText(std::string text)
{
    _text = std::move(text);
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
    _fontColor.r = static_cast<Uint8>(r);
    _fontColor.g = static_cast<Uint8>(g);
    _fontColor.b = static_cast<Uint8>(b);
    _fontColor.a = static_cast<Uint8>(a);
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
    if (_font == nullptr)
    {
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid((*_font).GetFont(), _text.c_str(), _fontColor);
    _output = SDL_CreateTextureFromSurface(&RenderSystem::Instance().GetRenderer(), textSurface);
    SDL_FreeSurface(textSurface);
}