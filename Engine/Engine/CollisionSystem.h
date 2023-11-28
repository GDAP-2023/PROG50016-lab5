#pragma once

#ifndef _COLLISIONSYSTEM_H
#define _COLLISIONSYSTEM_H

#include "ICollider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "EngineCore.h"
#include <utility>
#include "SDL.h"

class CollisionSystem
{
public:

	std::list<ICollider*> colliders;
	//for resolve collision, may need to make colliders a list of pairs of colliders and their last non-colliding position
	
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

	std::list<std::pair<ICollider*,ICollider*>> BroadPhaseDetection();
	//broad phase = narrow down what might be colliding, no need for square/circle specifics
	void ResolveCollision(ICollider*, ICollider*);
	struct Vector2;

protected:

	void Initialize();
	void Destroy();
	void Update();

	void SetID(ICollider*);

private:

	bool CircleCircleCollision(ICollider*, ICollider*);
	bool BoxBoxCollision(ICollider*, ICollider*);
	bool BoxCircleCollision(ICollider*, ICollider*);
	bool CheckCollisionBoundingVolumes(ICollider*, ICollider*);

private:
	static CollisionSystem* instance;
	std::list<int> idList;
	int idCount = 0;

	bool checkCollisionRough(ICollider*, ICollider*);

	friend class Engine;
	friend class ICollider;

private:
	inline explicit CollisionSystem() = default;
	inline ~CollisionSystem() = default;
	inline explicit CollisionSystem(CollisionSystem const&) = delete;
	inline CollisionSystem& operator=(CollisionSystem const&) = delete;
};

#endif