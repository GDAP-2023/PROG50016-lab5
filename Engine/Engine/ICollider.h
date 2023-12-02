#pragma once

#ifndef _ICOLLIDER_H
#define _ICOLLIDER_H

#include "EngineCore.h"
#include "SDL.h"
#include "Entity.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Math.h"
enum class ColliderType {
    Box,
    Circle,
    // ... potentially more collider types
};


/**
 * @class ICollider
 *
 * The ICollider class is an abstract class used by CollisionSystem, BoxCollider, and CircleCollider in order to store and call colliders regardless of type
 * Since it is an abstract class, its functions should never be called and instead should be implemented by its child classes BoxCollider and CircleCollider
 */
class ICollider : public Component
{
    DECLARE_ABSTRACT_DERIVED_CLASS(ICollider, Component);

protected:

    ICollider();
    ~ICollider() override;

protected:
    int size = 0;
    bool isSolid = false;

    Vec2 previousPosition;

public:
    /**
 * @brief Checks the bool isSolid to tell if this Entity should be treated as a solid object
 *
 * @return returns the boolean isSolid to tell if this Entity should be treated as solid
 */
    bool IsSolid() const;
    /**
 * @brief Sets the bool isSolid which tells if this Entity should be treated as a solid object
 *
 * @param solid True if the object should be solid, False if the object should not
 */
    void SetSolid(bool solid);

    virtual ColliderType GetType() const = 0;
    virtual float GetBroadPhaseRadius() const = 0;

    virtual Vec2 GetPosition() const = 0;

    virtual std::list<Entity*> OnCollisionEnter(ICollider*) = 0;
    virtual std::list<Entity*> OnCollisionStay(ICollider*) = 0;
    virtual std::list<Entity*> OnCollisionExit(ICollider*) = 0;
    virtual bool HandleCollision(ICollider*) = 0;

    void StorePosition(Vec2 position);

    void ResetPosition();

    friend class CollisionSystem;
};


#endif