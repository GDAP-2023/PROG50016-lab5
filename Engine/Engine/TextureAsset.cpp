#include "EngineCore.h"
#include "TextureAsset.h"
#include "RenderSystem.h"

IMPLEMENT_DYNAMIC_CLASS(TextureAsset);

void TextureAsset::Initialize()
{
	Asset::Initialize();
}

void TextureAsset::Destroy()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;

	Asset::Destroy();
}

void TextureAsset::Load(json::JSON& json)
{
	Asset::Load(json);
	SDL_Surface* image = IMG_Load(filepath.c_str());
	texture = SDL_CreateTextureFromSurface(&RenderSystem::Instance().GetRenderer(), image);
	SDL_FreeSurface(image);
}
