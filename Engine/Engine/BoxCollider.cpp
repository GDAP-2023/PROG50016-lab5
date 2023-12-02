// By Alan
// BoxCollider.cpp
// For Lab 5
 
#include "EngineCore.h"
#include "BoxCollider.h"

IMPLEMENT_DYNAMIC_CLASS(BoxCollider);

//
BoxCollider::BoxCollider():m_rect({0,0,0,0})
{
	int myID = GetId();
	Entity* thisEntity = SceneManager::Get().FindEntityById(myID);
	transform = (Transform*)thisEntity->GetComponent("Transform");

	if (thisEntity->HasComponent("Sprite"))
	{
		m_rect = thisEntity->((Sprite)GetComponent("Sprite")).sourceRect;
	}
	else if (thisEntity->HasComponent("AnimatedSprite"))
	{
		m_rect = thisEntity->((AnimatedSprite)GetComponent("AnimatedSprite")).sourceRect;
	}

	CollisionSystem::Instance().AddCollider(this);
}

BoxCollider::~BoxCollider()
{
	CollisionSystem::Instance().RemoveCollider(this);
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
	m_rect= { transform.x, transform.y, width, height };
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
		if (((Component*)collisionPairs.first)->GetId() != ((Component*)collisionPairs.second)->GetId())
		{
			if (((Component*)collisionPairs.first)->GetId() == ((Component*)other)->GetId() && ((Component*)collisionPairs.second)->GetId() == GetId())
			{
				int otherId = ((Component*)other)->GetId();
				Entity* toAdd = SceneManager::Get().FindEntityById(otherId);
				result.push_back(toAdd);
			}
			else if (((Component*)collisionPairs.second)->GetId() == ((Component*)other)->GetId() && ((Component*)collisionPairs.first)->GetId() == GetId())
			{
				int otherId = ((Component*)other)->GetId();
				Entity* toAdd = SceneManager::Get().FindEntityById(otherId);
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
		if (((Component*)collisionPairs.first)->GetId() != ((Component*)collisionPairs.second)->GetId())
		{
			if (((Component*)collisionPairs.first)->GetId() == ((Component*)other)->GetId() && ((Component*)collisionPairs.second)->GetId() == GetId())
			{
				int otherId = ((Component*)other)->GetId();
				Entity* toAdd = SceneManager::Get().FindEntityById(otherId);
				result.push_back(toAdd);
			}
			else if (((Component*)collisionPairs.second)->GetId() == ((Component*)other)->GetId() && ((Component*)collisionPairs.first)->GetId() == GetId())
			{
				int otherId = ((Component*)other)->GetId();
				Entity* toAdd = SceneManager::Get().FindEntityById(otherId);
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
		if (((Component*)collisionPairs.first)->GetId() != ((Component*)collisionPairs.second)->GetId())
		{
			if (((Component*)collisionPairs.first)->GetId() == ((Component*)other)->GetId() && ((Component*)collisionPairs.second)->GetId() == GetId())
			{
				int otherId = ((Component*)other)->GetId();
				Entity* toAdd = SceneManager::Get().FindEntityById(otherId);
				result.push_back(toAdd);
			}
			else if (((Component*)collisionPairs.second)->GetId() == ((Component*)other)->GetId() && ((Component*)collisionPairs.first)->GetId() == GetId())
			{
				int otherId = ((Component*)other)->GetId();
				Entity* toAdd = SceneManager::Get().FindEntityById(otherId);
				result.push_back(toAdd);
			}
		}
	}
	return result;
}



bool BoxCollider::IsSolid() const
{
	return isSolid;
}
void BoxCollider::SetSolid(bool solid)
{
	isSolid = solid;
}