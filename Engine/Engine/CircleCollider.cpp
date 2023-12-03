#include "EngineCore.h"
#include "CircleCollider.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

IMPLEMENT_DYNAMIC_CLASS(CircleCollider);
/**
 * @brief Constructor for CircleCollider. Initializes the collider and registers it with the CollisionSystem.
 */
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

/**
 * @brief Update method for CircleCollider. Currently not implemented.
 */
void CircleCollider::Update()
{
}
/**
 * @brief Destructor for CircleCollider. Removes the collider from the CollisionSystem.
 */
CircleCollider::~CircleCollider()
{
	CollisionSystem::Instance().RemoveCollider(this);
}
/**
 * @brief Destroy method for CircleCollider. Currently not implemented.
 */
void CircleCollider::Destroy()
{

}
/**
 * @brief Handles collision with another collider. Currently always returns true.
 *
 * @param other The other collider involved in the collision.
 * @return Always returns true.
 */
bool CircleCollider::HandleCollision(ICollider* other)
{
	return true;
}
/**
 * @brief Gets the position of the CircleCollider.
 *
 * @return The position of the collider as a Vec2.
 */
Vec2 CircleCollider::GetPosition() const
{
	//return Vec2(transform.x, transform.y);
	Vec2 tempVec = Vec2(0, 0);
	return tempVec;
}

/**
 * @brief Sets the radius of the CircleCollider.
 *
 * @param radius The new radius for the collider.
 */
void CircleCollider::SetRadius(float radius)
{
	m_radius = radius;
}

/**
 * @brief Gets the radius of the CircleCollider.
 *
 * @return The radius of the collider.
 */
float CircleCollider::GetRadius()
{
	return m_radius;
}
/**
 * @brief Calculates the broad phase radius of the CircleCollider.
 *
 * @return The radius of the collider.
 */
float CircleCollider::GetBroadPhaseRadius() const
{
	return m_radius;
}
/**
 * @brief Gets the type of the collider.
 *
 * @return The type of the collider, in this case Circle.
 */
ColliderType CircleCollider::GetType() const
{
	return ColliderType::Circle;
}


/**
 * @brief Called when the collider enters a collision.
 *
 * @param other The other collider involved in the collision.
 * @return A list of entities involved in the collision.
 */
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


/**
 * @brief Called when the collider stays in collision.
 *
 * @param other The other collider involved in the collision.
 * @return A list of entities involved in the collision.
 */
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

/**
 * @brief Called when the collider exits a collision.
 *
 * @param other The other collider involved in the collision.
 * @return A list of entities that were involved in the collision.
 */
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
/**
 * @brief Checks if the CircleCollider is solid.
 *
 * @return True if the collider is solid, false otherwise.
 */
bool CircleCollider::IsSolid() const
{
	return isSolid;
}
/**
 * @brief Sets the solid state of the CircleCollider.
 *
 * @param solid True to make the collider solid, false otherwise.
 */
void CircleCollider::SetSolid(bool solid)
{
	isSolid= solid;
}