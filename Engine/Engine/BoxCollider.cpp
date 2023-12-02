#include "EngineCore.h"
#include "BoxCollider.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

IMPLEMENT_DYNAMIC_CLASS(BoxCollider);

BoxCollider::BoxCollider()
{
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
	//return Vec2(ownerEntity->GetTransform().x, ownerEntity->GetTransform().y);
	Vec2 tempVec = Vec2(0, 0);
	return tempVec;
}

void BoxCollider::SetSize(int width,int height)
{
	m_rect= { (int) ownerEntity->GetTransform()->position.x, (int)ownerEntity->GetTransform()->position.y, width, height };
}


float BoxCollider::GetBroadPhaseRadius() const
{
	return Vec2(m_rect.w, m_rect.h).Magnitude();
}

ColliderType BoxCollider::GetType() const
{
	return ColliderType::Box;
}

// Called when the collider enters a collision
std::list<Entity*> BoxCollider::OnCollisionEnter(ICollider* other) {
	std::list<Entity*> result;
	for (auto collisionPairs : CollisionSystem::Instance().enterCollisions)
	{
		if (((Component*)collisionPairs.first)->GetUid() != ((Component*)collisionPairs.second)->GetUid())
		{
			if (((Component*)collisionPairs.first)->GetUid() == ((Component*)other)->GetUid() && ((Component*)collisionPairs.second)->GetUid() == GetUid())
			{
				int otherId = ((Component*)other)->GetUid();
				Entity* toAdd = SceneManager::Get().FindEntity(otherId);
				result.push_back(toAdd);
			}
			else if (((Component*)collisionPairs.second)->GetUid() == ((Component*)other)->GetUid() && ((Component*)collisionPairs.first)->GetUid() == GetUid())
			{
				int otherId = ((Component*)other)->GetUid();
				Entity* toAdd = SceneManager::Get().FindEntity(otherId);
				result.push_back(toAdd);
			}
		}
	}
	return result;
}

// Called when the collider stays in collision
std::list<Entity*> BoxCollider::OnCollisionStay(ICollider* other) {
	std::list<Entity*> result;
	for (auto collisionPairs : CollisionSystem::Instance().stayCollisions)
	{
		if (((Component*)collisionPairs.first)->GetUid() != ((Component*)collisionPairs.second)->GetUid())
		{
			if (((Component*)collisionPairs.first)->GetUid() == ((Component*)other)->GetUid() && ((Component*)collisionPairs.second)->GetUid() == GetUid())
			{
				int otherId = ((Component*)other)->GetUid();
				Entity* toAdd = SceneManager::Get().FindEntity(otherId);
				result.push_back(toAdd);
			}
			else if (((Component*)collisionPairs.second)->GetUid() == ((Component*)other)->GetUid() && ((Component*)collisionPairs.first)->GetUid() == GetUid())
			{
				int otherId = ((Component*)other)->GetUid();
				Entity* toAdd = SceneManager::Get().FindEntity(otherId);
				result.push_back(toAdd);
			}
		}
	}
	return result;
}

// Called when the collider exits a collision
std::list<Entity*> BoxCollider::OnCollisionExit(ICollider* other) {
	std::list<Entity*> result;
	for (auto collisionPairs : CollisionSystem::Instance().exitCollisions)
	{
		if (((Component*)collisionPairs.first)->GetUid() != ((Component*)collisionPairs.second)->GetUid())
		{
			if (((Component*)collisionPairs.first)->GetUid() == ((Component*)other)->GetUid() && ((Component*)collisionPairs.second)->GetUid() == GetUid())
			{
				int otherId = ((Component*)other)->GetUid();
				Entity* toAdd = SceneManager::Get().FindEntity(otherId);
				result.push_back(toAdd);
			}
			else if (((Component*)collisionPairs.second)->GetUid() == ((Component*)other)->GetUid() && ((Component*)collisionPairs.first)->GetUid() == GetUid())
			{
				int otherId = ((Component*)other)->GetUid();
				Entity* toAdd = SceneManager::Get().FindEntity(otherId);
				result.push_back(toAdd);
			}
		}
	}
	return result;
}
