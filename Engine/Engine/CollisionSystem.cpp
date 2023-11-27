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

}

void CollisionSystem::AddCollider(ICollider* collider)
{

}

void CollisionSystem::RemoveCollider(ICollider* collider)
{

}

void CollisionSystem::SetID(ICollider* collider)
{

}

std::list<std::pair<ICollider, ICollider>> CollisionSystem::BroadPhaseDetection()
{

}

void CollisionSystem::ResolveCollision(ICollider* col1, ICollider* col2)
{

}