#pragma once

#ifndef  _TEXTURE_ASSET_H_
#define _TEXTURE_ASSET_H_

#include "Asset.h"
#include "SDL_image.h"

class TextureAsset final : public Asset {
private:

	SDL_Texture* texture;

public:

	TextureAsset(SDL_Texture* t) : texture(t) {}

	~TextureAsset() {}
};

#endif // !_TEXTURE_ASSET_H_
