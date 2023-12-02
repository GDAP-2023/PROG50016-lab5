#include "EngineCore.h"
#include "MusicAsset.h"

IMPLEMENT_DYNAMIC_CLASS(MusicAsset)

void MusicAsset::Initialize()
{
	Asset::Initialize();
}

void MusicAsset::Destroy()
{
	Asset::Destroy();
}

void MusicAsset::Load(json::JSON& json)
{
	Asset::Load(json);
};
