#pragma once
#ifndef _CIRCLECOLLIDER_H_
#define _CIRCLECOLLIDER_H_

#include"EngineCore.h"
#include"ICollider.h"
#include"Component.h"
#include"CollisionSystem.h"
/**
 * @class CircleCollider
 *
 * The CircleCollider class is a type of component added to an entity that represents a circle around the entity where collisions will occur
 * It is a circle centred on the entity with a radius of m_radius
 * To check for collisions, use the OnCollisionEnter, OnCollisionStay, or OnCollisionExit functions and consult their implementation
 */
class CircleCollider : public ICollider
{
	DECLARE_DYNAMIC_DERIVED_CLASS(CircleCollider, ICollider);

private:
	float m_radius;
	SDL_Rect m_rect;
	bool isSolid = false;
	Transform* transform;
public:
	/**
 * @brief CircleCollider Constructor. Gets transform but not radius
 */
	CircleCollider();
protected:
	~CircleCollider();
	void Update() override;  // declared in Component
	void Destroy();

public:
	/**
 * @brief Sets the radius of the collider
 *
 * @param radius A float value that the collider's radius will be set to
 */
	void SetRadius(float radius);
	/**
 * @brief returns radius, really this is just a GetRadius function
 *
 * @return returns the float radius of the collider
 */
	float GetRadius();
	float GetBroadPhaseRadius() const;

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

	/**
 * @brief Currently unimplemented, would use the isSolid variable to prevent two solid objects from overlapping
 *
 * @param other The other solid collider object that the CollisionSystem has found you to be colliding with
 * @return Always returns true
 */
	bool HandleCollision(ICollider* other);

	/**
 * @brief Currently unimplemented, should return the x,y values of the transform attached to this collider's attached object
 *
 * @return Returns a Vec2 with values 0,0 always since unimplemented
 */
	Vec2 GetPosition() const override;

	/**
* @brief Used to tell if this collider is a Circle or Box collider
*
* @return Returns the collider type, in this case CircleCollider
*/
	ColliderType GetType() const override;

	/**
* @brief Used for handling collisions that have just started occuring by checking if another collider collides with you
*
* @param other The other collider you want to check if there's been a collision with
* @return Either an empty list if you did not just collide with other, or a list that only contains other's game Entity if you did collide with other
*/
	std::list<Entity*> OnCollisionEnter(ICollider* other);

	/**
* @brief Used for handling collisions that have been occuring for more than one run of code by checking if another collider collides with you
*
* @param other The other collider you want to check if there's been a collision with
* @return Either an empty list if you did not collide with other, or a list that only contains other's game Entity if you did collide with other
*/
	std::list<Entity*> OnCollisionStay(ICollider* other);

	/**
* @brief Used for handling collisions that have just stopped occuring by checking if another collider collides with you
*
* @param other The other collider you want to check if there's been a collision with
* @return Either an empty list if you did not just stop colliding with other, or a list that only contains other's game Entity if you did stop colliding with other
*/
	std::list<Entity*> OnCollisionExit(ICollider* other);



};

#endif
