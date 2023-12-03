#include "EngineCore.h"
#include "CircleCollider.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

IMPLEMENT_DYNAMIC_CLASS(CircleCollider);

void CircleCollider::Update()
{
}

void CircleCollider::Initialize()
{
    ICollider::Initialize();
	if (ownerEntity->HasComponent("Sprite"))
	{
		m_rect = ((Sprite*)(ownerEntity->GetComponent("Sprite")))->targetRect;
	}
	else if (ownerEntity->HasComponent("AnimatedSprite"))
	{
		m_rect = ((AnimatedSprite*)(ownerEntity->GetComponent("AnimatedSprite")))->targetRect;
	}
}

void CircleCollider::Destroy()
{

}

bool CircleCollider::HandleCollision(ICollider* other)
{
	return true;
}

Vec2 CircleCollider::GetPosition() const
{
	return ownerEntity->GetTransform().position;
}

// Set the radius of the collider
void CircleCollider::SetRadius(float radius)
{
	m_radius = radius;
}

float CircleCollider::GetRadius() const
{
	return m_radius;
}

float CircleCollider::GetBroadPhaseRadius() const
{
	return m_radius;
}
ColliderType CircleCollider::GetType() const
{
	return ColliderType::Circle;
}