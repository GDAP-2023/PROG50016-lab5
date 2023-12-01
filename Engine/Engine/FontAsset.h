#pragma once
#ifndef _FONT_ASSET_H_
#define _FONT_ASSET_H_

#include "Asset.h"
#include "SDL_ttf.h"


class FontAsset : public Asset
{
    TTF_Font* font = nullptr;

	DECLARE_DYNAMIC_DERIVED_CLASS(FontAsset, Asset)
    FontAsset();
    ~FontAsset() override;
    void Initialize() override;
    void Destroy() override;
    void Load(json::JSON&) override;
};

#endif // !_FONT_ASSET_H_
