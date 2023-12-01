#include "EngineCore.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider():
{
	int myID = GetId();
	Entity* thisEntity = SceneManager::Get().FindEntityById(myID);
	transform = (Transform*)thisEntity->GetComponent("Transform"); //don't forget to (cast) to Transform once implemented
	//grab rect


	//set radius
	if (thisEntity->HasComponent("Sprite"))
	{
		m_rect = thisEntity->((Sprite)GetComponent("Sprite")).sourceRect;
	}
	else if (thisEntity->HasComponent("AnimatedSprite"))
	{
		m_rect = thisEntity->((AnimatedSprite)GetComponent("AnimatedSprite")).sourceRect;
	}
	m_radius = Vec2(m_rect.w, m_rect.h).Magnitude();

	CollisionSystem::Instance().AddCollider(this);
}


CircleCollider::~CircleCollider()
{
	CollisionSystem::Instance().RemoveCollider(this);
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
	//return Vec2(transform.x, transform.y);
	Vec2 tempVec = Vec2(0, 0);
	return tempVec;
}

// Set the radius of the collider
void CircleCollider::SetRadius(float radius)
{
	m_radius = radius;
}

float CircleCollider::GetBroadPhaseRadius() const
{
	return m_radius;
}
ColliderType CircleCollider::GetType() const
{
	return ColliderType::Circle;
}


// Called when the collider enters a collision
std::list<Entity*> CircleCollider::OnCollisionEnter(ICollider* other) {
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
std::list<Entity*> CircleCollider::OnCollisionStay(ICollider* other) {
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
std::list<Entity*> CircleCollider::OnCollisionExit(ICollider* other) {
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

bool CircleCollider::IsSolid() const
{
	return isSolid;
}
void CircleCollider::SetSolid(bool solid)
{
	isSolid= solid;
}