#pragma once

#ifndef _ICOLLIDER_H
#define _ICOLLIDER_H

#include "EngineCore.h"

class ICollider
{
private:

	ICollider();
	~ICollider();

protected:
	virtual void Destroy() = 0;

public:

	std::string id;

	virtual void OnCollisionEnter(ICollider*) = 0;
	virtual void OnCollisionExit(ICollider*) = 0;
	virtual bool CheckCollision(ICollider) = 0;

	friend class CollisionSystem;
};


#endif