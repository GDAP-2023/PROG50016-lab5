#include "EngineCore.h"
#include "FontAsset.h"

IMPLEMENT_DYNAMIC_CLASS(FontAsset)

void FontAsset::Initialize()
{
	Asset::Initialize();
}

void FontAsset::Destroy()
{
	Asset::Destroy();
}

void FontAsset::Load(json::JSON& json)
{
	Asset::Load(json);
};
