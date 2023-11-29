#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "InputSystem.h"
#include <functional>

class Player {
public:
    Player(float x, float y, float speed);
    ~Player();

    void update(const InputSystem& inputSystem);
    void render();  // Assuming you have some graphics system

    // Movement methods
    void moveLeft();
    void moveRight();

    void moveUp();

    void moveDown();

    // Getters and setters for position, speed, etc.
    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);

private:
    float posX, posY;  // Player position
    float speed;       // Movement speed

    // Additional player attributes
    float health;
    int score;
    const int gamepadDeadzone = 8000;
    int gamepadId = 0;

    // Helper methods for complex behaviors
    void handleCollisions();
    void updatePhysics();
};

#endif // PLAYER_H

