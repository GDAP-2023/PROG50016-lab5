#pragma once

#ifndef _MA_H_
#define _MA_H_

#include "Asset.h"

class Mix_Music;

class MusicAsset :
    public Asset
{
private:
    
    Mix_Music* _musicAsset;

public:
    MusicAsset(Mix_Music* m) : _musicAsset(m) {};

    ~MusicAsset() {};
};

#endif // !_MA_H_
