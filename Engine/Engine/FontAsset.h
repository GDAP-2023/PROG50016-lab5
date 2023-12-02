#pragma once
#ifndef _FONT_ASSET_H_
#define _FONT_ASSET_H_

#include "Asset.h"
#include "SDL_ttf.h"


class FontAsset : public Asset
{
    TTF_Font* font = nullptr;

	DECLARE_DYNAMIC_DERIVED_CLASS(FontAsset, Asset)
    FontAsset() = default;
    ~FontAsset() override = default;
    void Initialize() override;
    void Destroy() override;
    void Load(json::JSON&) override;
    TTF_Font* GetFont() const
    {
	    return font;
    }
};

#endif // !_FONT_ASSET_H_
