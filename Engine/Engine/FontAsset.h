#pragma once
#ifndef _FA_H_
#define _FA_H_

#include "Asset.h"

class TTF_Font;

class FontAsset :
    public Asset
{
    TTF_Font* _font;

public:
    FontAsset(TTF_Font* f) : _font(f) {};

    ~FontAsset() {};
};

#endif // !_FA_H_
