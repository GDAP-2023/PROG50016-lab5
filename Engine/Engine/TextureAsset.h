#pragma once

#ifndef  _TA_H_
#define _TA_H_

#include "Asset.h"

class SDL_Texture;

class TextureAsset :
    public Asset
{
private:

    SDL_Texture* _texture;

public: 
    
    TextureAsset(SDL_Texture* t) : _texture(t) {};

    ~TextureAsset() {};
};

#endif // ! _TA_H_
