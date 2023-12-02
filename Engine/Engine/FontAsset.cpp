#include "EngineCore.h"
#include "FontAsset.h"

IMPLEMENT_DYNAMIC_CLASS(FontAsset)

void FontAsset::Initialize()
{
	font = TTF_OpenFont(filepath.c_str(), font_size);
	Asset::Initialize();
}

void FontAsset::Destroy()
{
	TTF_CloseFont(font);
	font = nullptr;
	Asset::Destroy();
}

void FontAsset::Load(json::JSON& node)
{
	Asset::Load(node);
	if (node.hasKey("FontSize"))
	{
		font_size = node.at("FontSize").ToInt();
	}
}

TTF_Font* FontAsset::GetFont() const
{
	return font;
};
