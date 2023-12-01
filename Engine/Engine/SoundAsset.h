#pragma once

#ifndef _SOUND_ASSET_H_
#define _SOUND_ASSET_H_

#include "Asset.h"
#include "SDL_mixer.h"

class SoundAsset :
    public Asset
{
public:
    Mix_Chunk* _soundAsset;

    SoundAsset(Mix_Chunk* s) : _soundAsset(s) {};

    ~SoundAsset() {};
};

#endif // !_SOUND_ASSET_H_
