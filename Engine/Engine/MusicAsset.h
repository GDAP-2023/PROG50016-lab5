#pragma once

#ifndef _MUSIC_ASSET_H_
#define _MUSIC_ASSET_H_

#include "Asset.h"
#include "SDL_mixer.h"

class MusicAsset : public Asset {
private:

	Mix_Music* _musicAsset;

public:
	MusicAsset(Mix_Music* m) : _musicAsset(m) {};

	~MusicAsset() {};
};

#endif // !_MUSIC_ASSET_H_
