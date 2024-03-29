#include "EngineCore.h"
#include "CollisionSystem.h"
#include "AnimatedSprite.h"

IMPLEMENT_ABSTRACT_CLASS(ICollider);

ICollider::ICollider() {
	CollisionSystem::Instance().AddCollider(this);
}

ICollider::~ICollider() {
	CollisionSystem::Instance().RemoveCollider(this);
}

void ICollider::Initialize()
{
	Component::Initialize();
	if (ownerEntity->HasComponent("Sprite"))
	{
		// TODO: unsafe if our Sprite Component is destroyed.
		m_rect = &((Sprite*)(ownerEntity->GetComponent("Sprite")))->targetRect;
	}
	else if (ownerEntity->HasComponent("AnimatedSprite"))
	{
		// TODO: unsafe if our AnimatedSprite Component is destroyed.
		m_rect = &((AnimatedSprite*)(ownerEntity->GetComponent("AnimatedSprite")))->targetRect;
	}
}

/**
 * @brief store the position of the collider
 *
 * @param position
 */
void ICollider::StorePosition(const Vec2 position) {
	previousPosition = position;
}
/**
* @brief reset the position of the collider
* @param position
* */
	
void ICollider::ResetPosition() const
{
	ownerEntity->GetTransform().position = previousPosition;
}
/**
* @brief Gets the position of the collider.
* 
* @return The position of the collider.
* */

bool ICollider::IsSolid() const {
	return isSolid;
}
/**
* @brief Sets the solid state of the collider.
* 
* @param solid The new solid state of the collider.
* */
void ICollider::SetSolid(const bool solid) {
	isSolid = solid;
}

/**
*
* @brief Gets the position of the collider.
* 
* @return The position of the collider.
* */
Vec2 ICollider::GetPosition() const
{
	return ownerEntity->GetTransform().position;
}


std::list<ICollider*> ICollider::OnCollisionEnter() {
	std::list<ICollider*> result;
	for (const auto& [first, second] : CollisionSystem::Instance().enterCollisions) {
		// Skip checking for collisions if both Colliders are the same
		if (first->GetUid() == second->GetUid()) {
			continue;
		}

		if (first->GetUid() == GetUid()) {
			result.push_back(second);
		} else if (second->GetUid() == GetUid()) {
			result.push_back(first);
		}
	}
	return result;
}

// Called when the collider stays in collision
std::list<ICollider*> ICollider::OnCollisionStay() {
	std::list<ICollider*> result;
	for (const auto& [first, second] : CollisionSystem::Instance().stayCollisions) {
		// Skip checking for collisions if both Colliders are the same
		if (first->GetUid() == second->GetUid()) {
			continue;
		}

		if (first->GetUid() == GetUid()) {
			result.push_back(second);
		} else if (second->GetUid() == GetUid()) {
			result.push_back(first);
		}
	}
	return result;
}


// Called when the collider exits a collision
std::list<ICollider*> ICollider::OnCollisionExit() {
	std::list<ICollider*> result;
	for (const auto& [first, second] : CollisionSystem::Instance().exitCollisions) {
		// Skip checking for collisions if both Colliders are the same
		if (first->GetUid() == second->GetUid()) {
			continue;
		}

		if (first->GetUid() == GetUid()) {
			result.push_back(second);
		} else if (second->GetUid() == GetUid()) {
			result.push_back(first);
		}
	}
	return result;
}
