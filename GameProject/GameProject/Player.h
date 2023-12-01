#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "GameCore.h"
#include "InputSystem.h"
#include <functional>


#include "Component.h"

class Player : public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(Player, Component)

public:
    void Initialize() override;
    void Update(const InputSystem& inputSystem);
    virtual const std::string& GetComponentType();
private:
    float speed = 5.0f;
};

#endif // PLAYER_H


