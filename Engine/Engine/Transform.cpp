#include "EngineCore.h"
#include "Transform.h"

Transform::Transform() : position(Vec2::Zero), rotation(0.0f), scale(Vec2(1.0f, 1.0f)) {} //constructor & initialize pos to 0, rotation to 0, scale to 1

void Transform::Initialize() { // empty function but initial values are est in constructor

}

void Transform::Update() {

}

void Transform::Translate(const Vec2& delta) { // next 3 functions for adjusting position, rotation and scale by a given vector
    position += delta;
}

void Transform::Rotate(float delta) {
    rotation += delta;
}

void Transform::Scale(const Vec2& delta) {
    scale *= delta;
}
