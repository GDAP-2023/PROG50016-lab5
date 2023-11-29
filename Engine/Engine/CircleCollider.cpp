#include "EngineCore.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(): m_radius(0.0f)
{
	int myID = GetId();
	Entity* thisEntity = SceneManager::Get().FindEntityById(myID);
	//transform = thisEntity->GetComponent("Transform"); //don't forget to (cast) to Transform once implemented

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
		if (((Component*)collisionPairs.first)->GetId() == ((Component*)other)->GetId() && ((Component*)collisionPairs.second)->GetId() == GetId())
		{
			int otherId = ((Component*)other)->GetId();
			Entity* toAdd = SceneManager::Get().FindEntityById(otherId);;
			result.push_back(toAdd);
		}
		else if (((Component*)collisionPairs.second)->GetId() == ((Component*)other)->GetId() && ((Component*)collisionPairs.first)->GetId() == GetId())
		{
		
		}
	}
	return result;
}

// Called when the collider stays in collision
std::list<Entity*> CircleCollider::OnCollisionStay(ICollider* other) {
	std::list<Entity*> result;
	return result;
}

// Called when the collider exits a collision
std::list<Entity*> CircleCollider::OnCollisionExit(ICollider* other) {
	std::list<Entity*> result;
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