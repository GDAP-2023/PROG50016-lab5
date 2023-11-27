#pragma once

#ifndef _COLLISIONSYSTEM_H
#define _COLLISIONSYSTEM_H

#include "ICollider.h"
#include "EngineCore.h"
#include <utility>

class CollisionSystem
{
public:

	std::list<ICollider*> colliders;

public:
	static CollisionSystem& Instance()
	{
		if (instance == nullptr)
		{
			instance = new CollisionSystem();
		}
		return *instance;
	}

	void AddCollider(ICollider*);
	void RemoveCollider(ICollider*);

	std::list<std::pair<ICollider,ICollider>> BroadPhaseDetection();
	void ResolveCollision(ICollider*, ICollider*);

protected:

	void Initialize();
	void Destroy();
	void Update();

	void SetID(ICollider*);

private:
	static CollisionSystem* instance;

	friend class Engine;
	friend class ICollider;

private:
	inline explicit CollisionSystem() = default;
	inline ~CollisionSystem() = default;
	inline explicit CollisionSystem(CollisionSystem const&) = delete;
	inline CollisionSystem& operator=(CollisionSystem const&) = delete;
};

#endif