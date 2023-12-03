#include "EngineCore.h"
#include "BoxCollider.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

IMPLEMENT_DYNAMIC_CLASS(BoxCollider);
/**
 * @brief Constructor for BoxCollider. Initializes the collider and registers it with the CollisionSystem.
 */
BoxCollider::BoxCollider():m_rect({0,0,0,0})
{
	int myID = GetUid();
	Entity* thisEntity = SceneManager::Get().FindEntity(myID);
	transform = (Transform*)thisEntity->GetComponent("Transform");

	if (thisEntity->HasComponent("Sprite"))
	{
		m_rect = ((Sprite*)thisEntity->GetComponent("Sprite"))->targetRect;
	}
	else if (thisEntity->HasComponent("AnimatedSprite"))
	{
		m_rect = ((AnimatedSprite*)thisEntity->GetComponent("AnimatedSprite"))->targetRect;
	}

	CollisionSystem::Instance().AddCollider(this);
}
/**
 * @brief Destructor for BoxCollider. Removes the collider from the CollisionSystem.
 */
BoxCollider::~BoxCollider()
{
	CollisionSystem::Instance().RemoveCollider(this);
}
/**
 * @brief Update method for BoxCollider. Currently not implemented.
 */
void BoxCollider::Update()
{
}

/**
 * @brief Destroy method for BoxCollider. Currently not implemented.
 */
void BoxCollider::Destroy()
{

}
/**
 * @brief Handles collision with another collider. Currently not implemented.
 *
 * @param other The other collider involved in the collision.
 * @return Always returns false.
 */
bool BoxCollider::HandleCollision(ICollider* other)
{
	return false;
}
/**
 * @brief Gets the position of the BoxCollider.
 *
 * @return The position of the collider as a Vec2.
 */
Vec2 BoxCollider::GetPosition() const
{
	//return Vec2(transform.x, transform.y);
	Vec2 tempVec = Vec2(0, 0);
	return tempVec;
}
/**
 * @brief Sets the size of the BoxCollider.
 *
 * @param width The width of the collider.
 * @param height The height of the collider.
 */
void BoxCollider::SetSize(int width,int height)
{
	m_rect= { (int) transform->position.x, (int) transform->position.y, width, height };
}

/**
 * @brief Calculates the broad phase radius of the BoxCollider.
 *
 * @return The magnitude of the vector formed by the collider's width and height.
 */
float BoxCollider::GetBroadPhaseRadius() const
{
	return Vec2(m_rect.w, m_rect.h).Magnitude();
}
/**
 * @brief Gets the type of the collider.
 *
 * @return The type of the collider, in this case Box.
 */
ColliderType BoxCollider::GetType() const
{
	return ColliderType::Box;
}


/**
 * @brief Called when the collider enters a collision.
 *
 * @param other The other collider involved in the collision.
 * @return A list of entities involved in the collision.
 */
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
/**
 * @brief Called when the collider stays in a collision.
 *
 * @param other The other collider involved in the collision.
 * @return A list of entities involved in the collision.
 */
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

/**
 * @brief Called when the collider exits a collision.
 *
 * @param other The other collider involved in the collision.
 * @return A list of entities that were involved in the collision.
 */
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


/**
 * @brief Checks if the BoxCollider is solid.
 *
 * @return True if the collider is solid, false otherwise.
 */
bool BoxCollider::IsSolid() const
{
	return isSolid;
}
/**
 * @brief Sets the solid state of the BoxCollider.
 *
 * @param solid True to make the collider solid, false otherwise.
 */
void BoxCollider::SetSolid(bool solid)
{
	isSolid = solid;
}