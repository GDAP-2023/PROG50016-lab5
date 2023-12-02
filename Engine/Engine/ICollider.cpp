#include "EngineCore.h"

#include "ICollider.h"
#include "CollisionSystem.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

IMPLEMENT_ABSTRACT_CLASS(ICollider);

ICollider::ICollider() : m_rect({ 0,0,0,0 })
{
	CollisionSystem::Instance().AddCollider(this);
}

ICollider::~ICollider()
{
	CollisionSystem::Instance().RemoveCollider(this);
}

void ICollider::Initialize()
{
	if (ownerEntity->HasComponent("Sprite"))
	{
		m_rect = ((Sprite*)ownerEntity->GetComponent("Sprite"))->targetRect;
	}
	else if (ownerEntity->HasComponent("AnimatedSprite"))
	{
		m_rect = ((AnimatedSprite*)ownerEntity->GetComponent("AnimatedSprite"))->targetRect;
	}
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
