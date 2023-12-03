#include "EngineCore.h"
#include "BoxCollider.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

IMPLEMENT_DYNAMIC_CLASS(BoxCollider);

void BoxCollider::Initialize()
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

void BoxCollider::Update()
{
}

void BoxCollider::Destroy()
{

}

bool BoxCollider::HandleCollision(ICollider* other)
{
	return false;
}

Vec2 BoxCollider::GetPosition() const
{
	//return Vec2(transform.x, transform.y);
	Vec2 tempVec = Vec2(0, 0);
	return tempVec;
}

void BoxCollider::SetSize(int width,int height)
{
	m_rect= { (int) ownerEntity->GetTransform().position.x, (int) ownerEntity->GetTransform().position.y, width, height };
}


float BoxCollider::GetBroadPhaseRadius() const
{
	return Vec2(m_rect.w, m_rect.h).Magnitude();
}

ColliderType BoxCollider::GetType() const
{
	return ColliderType::Box;
}
