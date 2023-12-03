#include "EngineCore.h"
#include "BoxCollider.h"

IMPLEMENT_DYNAMIC_CLASS(BoxCollider);

bool BoxCollider::HandleCollision(ICollider* other)
{
	return false;
}

void BoxCollider::SetSize(int width,int height)
{
	*m_rect = { (int) ownerEntity->GetTransform().position.x, (int) ownerEntity->GetTransform().position.y, width, height };
}


float BoxCollider::GetBroadPhaseRadius() const
{
	return Vec2(m_rect->w, m_rect->h).Magnitude();
}

ColliderType BoxCollider::GetType() const
{
	return ColliderType::Box;
}
