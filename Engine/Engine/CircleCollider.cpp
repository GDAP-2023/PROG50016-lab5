#include "EngineCore.h"
#include "CircleCollider.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

IMPLEMENT_DYNAMIC_CLASS(CircleCollider);

CircleCollider::CircleCollider():m_rect({ 0,0,0,0 })
{
	int myID = GetUid();
	Entity* thisEntity = SceneManager::Get().FindEntity(myID);
	transform = (Transform*)thisEntity->GetComponent("Transform"); //don't forget to (cast) to Transform once implemented
	//grab rect


	//set radius
	if (thisEntity->HasComponent("Sprite"))
	{
		m_rect = ((Sprite*)thisEntity->GetComponent("Sprite"))->targetRect;
	}
	else if (thisEntity->HasComponent("AnimatedSprite"))
	{
		m_rect = ((AnimatedSprite*)thisEntity->GetComponent("AnimatedSprite"))->targetRect;
	}
	m_radius = Vec2(m_rect.w, m_rect.h).Magnitude();

	CollisionSystem::Instance().AddCollider(this);
}

void CircleCollider::Update()
{
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

float CircleCollider::GetRadius()
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


// Called when the collider enters a collision
std::list<Entity*> CircleCollider::OnCollisionEnter(ICollider* other) {
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
std::list<Entity*> CircleCollider::OnCollisionStay(ICollider* other) {
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
std::list<Entity*> CircleCollider::OnCollisionExit(ICollider* other) {
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

bool CircleCollider::IsSolid() const
{
	return isSolid;
}
void CircleCollider::SetSolid(bool solid)
{
	isSolid= solid;
}