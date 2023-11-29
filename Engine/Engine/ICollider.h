#pragma once

#ifndef _ICOLLIDER_H
#define _ICOLLIDER_H

#include "EngineCore.h"
#include "SDL.h"
#include "CollisionSystem.h"
#include "Entity.h"
#include "SceneManager.h"
#include "Math.h"

enum class ColliderType {
	Box,
	Circle,
	// ... potentially more collider types
};


class ICollider
{
protected: 
	int size = 0;
	int x = 0;
	int y = 0;
	bool isSolid = false;
	
	Vec2 previousPosition;

public:
	virtual bool IsSolid() const = 0 ;
	virtual void SetSolid(bool solid) = 0 ;

private:
	float GetRadius();
	SDL_Rect GetBounds();
	Component* transform;

protected:

	ICollider();
	~ICollider();

protected:
	virtual void Destroy() = 0;

public:

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