#pragma once

#ifndef _SA_H_
#define _SA_H_

#include "Asset.h"

class Mix_Chunk;

class SoundAsset :
    public Asset
{
public:

    Mix_Chunk* _soundAsset;

    SoundAsset(Mix_Chunk* s) : _soundAsset(s) {};

    ~SoundAsset() {};
};

#endif // !_SA_H_
