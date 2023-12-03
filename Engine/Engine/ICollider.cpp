#include "EngineCore.h"

#include "ICollider.h"

#include "CollisionSystem.h"

IMPLEMENT_ABSTRACT_CLASS(ICollider);

ICollider::ICollider() {
	CollisionSystem::Instance().AddCollider(this);
}

ICollider::~ICollider() {
	CollisionSystem::Instance().RemoveCollider(this);
}

void ICollider::StorePosition(Vec2 position) {
	previousPosition = position;
}

void ICollider::ResetPosition() {
	//TODO: RestPosition

}

bool ICollider::IsSolid() const {
	return isSolid;
}
void ICollider::SetSolid(const bool solid) {
	isSolid = solid;
}

// Called when the collider enters a collision
std::list<ICollider*> ICollider::OnCollisionEnter() {
	std::list<ICollider*> result;
	for (const auto [first, second] : CollisionSystem::Instance().enterCollisions) {
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
	for (const auto [first, second] : CollisionSystem::Instance().stayCollisions) {
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
	for (const auto [first, second] : CollisionSystem::Instance().exitCollisions) {
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
