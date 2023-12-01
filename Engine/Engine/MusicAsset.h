#pragma once

#ifndef _MUSIC_ASSET_H_
#define _MUSIC_ASSET_H_

#include "Asset.h"
#include "SDL_mixer.h"

class MusicAsset : public Asset {
	Mix_Music* music;

	DECLARE_DYNAMIC_DERIVED_CLASS(MusicAsset, Asset)
	MusicAsset();
    ~MusicAsset() override;
    void Initialize() override;
    void Destroy() override;
    void Load(json::JSON&) override;
};

#endif // !_MUSIC_ASSET_H_