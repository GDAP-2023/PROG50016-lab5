#include "EngineCore.h"
#include "CollisionSystem.h"


CollisionSystem* CollisionSystem::instance = nullptr;

void CollisionSystem::Initialize()
{

}

void CollisionSystem::Destroy()
{

}

void CollisionSystem::Update()
{
	std::list<std::pair<ICollider*, ICollider*>> potentialCollisions = BroadPhaseDetection();

	for (auto& colliderPair : potentialCollisions)
	{
		CheckCollisionBoundingVolumes(colliderPair.first, colliderPair.second);
	}

	/*
	for(auto& collider1 : colliders)
	{
		for (auto& collider2 : colliders)
		{
			ResolveCollision(collider1, collider2);
		}
	}*/
}

void CollisionSystem::AddCollider(ICollider* collider)
{
	colliders.push_back(collider);
}

void CollisionSystem::RemoveCollider(ICollider* collider)
{
	colliders.remove(collider);
}

void CollisionSystem::SetID(ICollider* collider)
{
	collider->id = "";
}

std::list<std::pair<ICollider*, ICollider*>> CollisionSystem::BroadPhaseDetection()
{
	//incomplete
	std::list<std::pair<ICollider*, ICollider*>> potentialCollisions;
	for (auto it1 = colliders.begin(); it1 != colliders.end(); ++it1) {
		for (auto it2 = std::next(it1); it2 != colliders.end(); ++it2) {

			ICollider* collider1 = *it1;
			ICollider* collider2 = *it2;


			// Calculate bounding circle for each collider, treating them all as circles for broad phase.
			float radius1 = collider1->GetBroadPhaseRadius();
			float radius2 = collider2->GetBroadPhaseRadius();

			Vector2 position1 = collider1->GetPosition();
			Vector2 position2 = collider2->GetPosition();

			Vector2 positionDiff = position1 - position2;
			float radiusSum = radius1 + radius2;
			if(positionDiff.LengthSquared()<= (radiusSum * radiusSum))
			{
				potentialCollisions.push_back(std::make_pair(collider1, collider2));
			}
		}
	}

	return potentialCollisions;
}




void CollisionSystem::ResolveCollision(ICollider* col1, ICollider* col2)
{

}

bool CollisionSystem::CheckCollisionBoundingVolumes(ICollider* collider1, ICollider* collider2) {
	ColliderType type1 = collider1->GetType();
	ColliderType type2 = collider2->GetType();

	if (type1 == ColliderType::Circle && type2 == ColliderType::Circle) {
		return CircleCircleCollision(static_cast<CircleCollider*>(collider1), static_cast<CircleCollider*>(collider2));
	}
	else if (type1 == ColliderType::Box && type2 == ColliderType::Box) {
		return BoxBoxCollision(static_cast<BoxCollider*>(collider1), static_cast<BoxCollider*>(collider2));
	}
	else if (type1 == ColliderType::Box && type2 == ColliderType::Circle) {
		return BoxCircleCollision(static_cast<BoxCollider*>(collider1), static_cast<CircleCollider*>(collider2));
	}
	else if (type1 == ColliderType::Circle && type2 == ColliderType::Box) {
		return BoxCircleCollision(static_cast<BoxCollider*>(collider2), static_cast<CircleCollider*>(collider1));
	}
	return false; // If types do not match any known collision checks
}


float DistanceSquared(const CollisionSystem::Vector2& a, const CollisionSystem::Vector2& b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return dx * dx + dy * dy;
}

// Helper function for Circle-Circle collision
bool CollisionSystem::CircleCircleCollision(ICollider* circle1, ICollider* circle2) {
	Vector2 positionDiff = circle1->GetPosition() - circle2->GetPosition();
	float radiusSum = circle1->GetRadius() + circle2->GetRadius();
	return positionDiff.LengthSquared() <= (radiusSum * radiusSum);
}

// Helper function for Box-Box collision using AABB (Axis-Aligned Bounding Box)
bool CollisionSystem::BoxBoxCollision(ICollider* box1, ICollider* box2) {
	auto bounds1 = box1->GetBounds();
	auto bounds2 = box2->GetBounds();

	// Check if one box is to the left of the other or above the other
	return !(bounds1.x + bounds1.w < bounds2.x || bounds2.x + bounds2.w < bounds1.x ||
		bounds1.y + bounds1.h < bounds2.y || bounds2.y + bounds2.h < bounds1.y);
}

// Helper function for Box-Circle collision
/*
bool CollisionSystem::BoxCircleCollision(ICollider* box, ICollider* circle) {
	auto bounds = box->GetBounds();
	Vector2 circleCenter = circle->GetPosition();
	float circleRadius = circle->GetRadius();

	// Find the closest point on the AABB to the circle center
	float closestX = std::max(bounds.x, std::min(circleCenter.x, bounds.x + bounds.w));
	float closestY = std::max(bounds.y, std::min(circleCenter.y, bounds.y + bounds.h));

	// Calculate the distance between the circle's center and this closest point
	Vector2 closestPoint(closestX, closestY);
	float distanceSquared = (circleCenter - closestPoint).LengthSquared();

	// If the distance is less than the circle's radius, an intersection occurs
	return distanceSquared < (circleRadius * circleRadius);
}
*/

struct CollisionSystem::Vector2
{
	float x, y = 0;

	Vector2(float x, float y) : x(x), y(y) {}

	// Overload the - operator to get the difference between two vectors
	Vector2 operator-(const Vector2& rhs) const {
		return Vector2(x - rhs.x, y - rhs.y);
	}

	float LengthSquared() const {
		return x * x + y * y;
	}
};
