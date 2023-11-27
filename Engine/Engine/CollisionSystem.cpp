#include "EngineCore.h"
#include "CollisionSystem.h"

CollisionSystem* CollisionSystem::instance = nullptr;

void CollisionSystem::Initialize()
{

}

void CollisionSystem::Destroy()
{

}

void CollisionSystem::Update()
{
	std::list<std::pair<ICollider*, ICollider*>> viablePairs = BroadPhaseDetection();

	for (auto& colliderPair : viablePairs)
	{
		colliderPair.first->CheckCollision(colliderPair.second);
	}
}

void CollisionSystem::AddCollider(ICollider* collider)
{
	colliders.push_back(collider);
}

void CollisionSystem::RemoveCollider(ICollider* collider)
{
	colliders.remove(collider);
}

void CollisionSystem::SetID(ICollider* collider)
{
	std::string _id;
	_id += idCount;
	collider->id = _id;
	idCount++;
}

std::list<std::pair<ICollider*, ICollider*>> CollisionSystem::BroadPhaseDetection()
{
	std::list<std::pair<ICollider*, ICollider*>> result;
	for (auto& collider1 : colliders)
	{
		for (auto& collider2 : colliders)
		{
			if (collider1 != collider2)
			{
				bool viable = false;
				viable = Instance().checkCollisionRough(collider1, collider2);

				if (viable) 
				{ 
					std::pair<ICollider*, ICollider*> newPair;
					newPair.first = collider1;
					newPair.second = collider2;
					result.push_back(newPair); 
				}
			}
		}
	}
}

bool CollisionSystem::checkCollisionRough(ICollider* col1, ICollider* col2)
{
	bool result = false;

	float xdif = col2->x - col1->x;
	float ydif = col2->y - col1->y;
	xdif = xdif * xdif;
	ydif = ydif * ydif;
	float distance = sqrt(xdif + ydif);
	float totalsize = col1->size + col2->size;

	if (totalsize > distance) { result = true; }

	return result;
}

void CollisionSystem::ResolveCollision(ICollider* col1, ICollider* col2)
{
	//maybe store both transform positions from last frame where not colliding and restore them to that
	//some collider pairs can overlap, need to handle that
	// 
	//PZZ
	//if zombie moves forward and collides with player, then we push it back to safe from
	//but other zombie now occupies that from, and we might not find that collision
	//need to have Scene Manager calling ResolveCollision when an object tries to move to check if moving is okay
}