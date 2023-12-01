#pragma once

#ifndef  _TEXTURE_ASSET_H_
#define _TEXTURE_ASSET_H_

#include "Asset.h"
#include "SDL_image.h"

class TextureAsset final : public Asset {
    SDL_Texture* texture = nullptr;

	DECLARE_DYNAMIC_DERIVED_CLASS(TextureAsset, Asset)
    TextureAsset();
    ~TextureAsset() override;
    void Initialize() override;
    void Destroy() override;
    void Load(json::JSON&) override;
};

#endif // !_TEXTURE_ASSET_H_
