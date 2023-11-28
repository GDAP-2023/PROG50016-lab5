#pragma once

#ifndef _ICOLLIDER_H
#define _ICOLLIDER_H

#include "EngineCore.h"

enum class ColliderType {
	Box,
	Circle,
	// ... potentially more collider types
};
class ICollider
{
private: 
	int size = 0;
	int x = 0;
	int y = 0;

protected:

	ICollider();
	~ICollider();

protected:
	virtual void Destroy() = 0;

public:

	std::string id;

	virtual ColliderType GetType() const = 0;
	virtual float GetBroadPhaseRadius() const = 0;
	virtual Vector2 GetPosition() const = 0;

	virtual void OnCollisionEnter(ICollider*) = 0;
	virtual void OnCollisionExit(ICollider*) = 0;
	virtual bool CheckCollision(ICollider*) = 0;

	friend class CollisionSystem;
};


#endif