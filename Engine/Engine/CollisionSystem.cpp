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
	for(auto& collider1 : colliders)
	{
		for (auto& collider2 : colliders)
		{
			ResolveCollision(collider1, collider2);
		}
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
	collider->id = "";
}

std::list<std::pair<ICollider, ICollider>> CollisionSystem::BroadPhaseDetection()
{

}

void CollisionSystem::ResolveCollision(ICollider* col1, ICollider* col2)
{

}