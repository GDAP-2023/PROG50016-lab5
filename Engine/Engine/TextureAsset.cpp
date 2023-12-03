#include "EngineCore.h"
#include "TextureAsset.h"
#include "RenderSystem.h"

IMPLEMENT_DYNAMIC_CLASS(TextureAsset);

TextureAsset::TextureAsset()
{

}

void TextureAsset::Initialize()
{
	Asset::Initialize();
	filepath = "../Assets/" + filepath;
	SDL_Surface* image = IMG_Load(filepath.c_str());
	texture = SDL_CreateTextureFromSurface(&RenderSystem::Get().GetRenderer(), image);
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SDL_FreeSurface(image);
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
}

IVec2 TextureAsset::GetDimensions() const
{
	return IVec2(width, height);
}
