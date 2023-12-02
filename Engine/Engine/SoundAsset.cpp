#include "EngineCore.h"
#include "SoundAsset.h"

IMPLEMENT_DYNAMIC_CLASS(SoundAsset)

void SoundAsset::Initialize()
{
	Asset::Initialize();
}

void SoundAsset::Destroy()
{
	Asset::Destroy();
}

void SoundAsset::Load(json::JSON& json)
{
	Asset::Load(json);
};
