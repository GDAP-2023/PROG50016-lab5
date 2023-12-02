#include "EngineCore.h"

#include "ICollider.h"

#include "CollisionSystem.h"

IMPLEMENT_ABSTRACT_CLASS(ICollider);

ICollider::ICollider()
{
	CollisionSystem::Instance().AddCollider(this);
}

ICollider::~ICollider()
{
	CollisionSystem::Instance().RemoveCollider(this);
}

void ICollider::StorePosition(Vec2 position)
{
	previousPosition = position;
}

void ICollider::ResetPosition()
{
	//TODO: RestPosition
	
}

bool ICollider::IsSolid() const {
	return isSolid;
}
void ICollider::SetSolid(const bool solid) {
	isSolid = solid;
}