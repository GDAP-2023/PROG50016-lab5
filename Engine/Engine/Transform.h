#pragma once

#include "Component.h"
#include "EngineMath.h"  

class Transform : public Component {
public:
    Transform();

    //overriding virtual functions from Component
    void Initialize() override;
    void Update() override;

    //xyz properties, angle in degrees or radians
    Vec2 position;
    float rotation;
    Vec2 scale;

    //manipulating transform
    void Translate(const Vec2& delta);
    void Rotate(float delta);
    void Scale(const Vec2& delta);

    //getting and setting transform
    Vec2 GetPosition() const;
    float GetRotation() const;
    Vec2 GetScale() const;

    void SetPosition(const Vec2& newPosition);
    void SetRotation(float newRotation);
    void SetScale(const Vec2& newScale);
};
