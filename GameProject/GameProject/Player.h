#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameCore.h"

class Player : public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(Player, Component)

public:
    void Initialize() override;
    void Update() override;
private:
    float speed = 5.0f;
};

#endif // PLAYER_H


