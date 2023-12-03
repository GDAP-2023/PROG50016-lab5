#pragma once

#ifndef _BOXCOLLIDER_H_
#define _BOXCOLLIDER_H_

#include"EngineCore.h"
#include"ICollider.h"
#include"Component.h"
#include"CollisionSystem.h"
#include"SDL.h"
/**
 * @class BoxCollider
 *
 * The BoxCollider class is a type of component added to an entity that represents a rectangle around the entity where collisions will occur
 * It uses the entity's SDL_Rect as its position and bounds
 * To check for collisions, use the OnCollisionEnter, OnCollisionStay, or OnCollisionExit functions and consult their implementation
 */
class BoxCollider : public ICollider
{
	DECLARE_DYNAMIC_DERIVED_CLASS(BoxCollider, ICollider);

private:
	SDL_Rect m_rect;
public:
	/**
* @brief BoxCollider Constructor. Gets transform but not SDL_Rect values
*/
	BoxCollider() = default;

protected:
	~BoxCollider() override = default;
	void Initialize() override;
	void Update() override;  // declared in Component
	void Destroy() override;

public:
	/**
* @brief Sets the size of the collider
*
* @param width An int value that the collider's SDL_Rect's width will be set to
* @param height An int value that the collider's  SDL_Rect's height will be set to
*/
	void SetSize(int width, int height);

	/**
* @brief Currently unimplemented, should return the x,y values of the transform attached to this collider's attached object
*
* @return Returns a Vec2 with values 0,0 always since unimplemented
*/
	Vec2 GetPosition() const override;

	SDL_Rect GetBounds() { return m_rect; }

	/**
* @brief Used to tell if this collider is a Circle or Box collider
*
* @return Returns the collider type, in this case BoxCollider
*/
	ColliderType GetType() const override;

	/**
* @brief returns a float as if this box had a radius, this is needed for BroadPhaseDetection in CollisionSystem
*
* @return returns the length of the centre of the rect to the corner
*/
	float GetBroadPhaseRadius() const override;

	/**
* @brief Currently unimplemented, would use the isSolid variable to prevent two solid objects from overlapping
*
* @param other The other solid collider object that the CollisionSystem has found you to be colliding with
* @return Always returns false
*/
	bool HandleCollision(ICollider* other) override;
};


#endif