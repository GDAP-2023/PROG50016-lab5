#include "GameCore.h"
#include "GameOver.h"

IMPLEMENT_DYNAMIC_CLASS(GameOver)

void GameOver::Initialize()
{
    Component::Initialize();
    is_playing_audio = false;
}
void GameOver::Update() {
	sound_timer -= Time::Instance().DeltaTime();
    if (!is_playing_audio && sound_timer < 0.0f)
    {
        AudioSystem::Get().PlayFX(sound_fx);
        is_playing_audio = true;
    }
}
void GameOver::Load(json::JSON& node)
{
    Component::Load(node);
    if (node.hasKey("SoundTimer"))
    {
        sound_timer = static_cast<float>(node.at("SoundTimer").ToFloat());
    }

    if (node.hasKey("SceneToLoad"))
    {
	    scene_to_load = GetHashCode(node.at("SceneToLoad").ToString().c_str());
    }

    if (node.hasKey("Sound"))
    {
		std::string sound_asset_guid = node["Sound"].ToString();
	    sound_fx = (SoundAsset*)(AssetManager::Get().GetAsset(sound_asset_guid));
    }
}
