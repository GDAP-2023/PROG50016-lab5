#include "EngineCore.h"
#include "TextureAsset.h"

IMPLEMENT_DYNAMIC_CLASS(TextureAsset);

void TextureAsset::Destroy()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;

	Asset::Destroy();
}
