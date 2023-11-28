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

	NarrowPhaseDetection(potentialCollisions);

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

void CollisionSystem::NarrowPhaseDetection(const std::list<std::pair<ICollider*, ICollider*>>& potentialCollisions) {
	for (const auto& collisionPair : potentialCollisions) {
		ICollider* collider1 = collisionPair.first;
		ICollider* collider2 = collisionPair.second;

		bool isCollision = false;

		// Circle vs Circle Collision Check
		if (collider1->GetType() == ColliderType::Circle && collider2->GetType() == ColliderType::Circle) {
			isCollision = CircleCircleCollision(static_cast<CircleCollider*>(collider1), static_cast<CircleCollider*>(collider2));
		}
		// Box vs Box Collision Check (to be implemented)
		else if (collider1->GetType() == ColliderType::Box && collider2->GetType() == ColliderType::Box) {
			isCollision = BoxBoxCollision(static_cast<BoxCollider*>(collider1), static_cast<BoxCollider*>(collider2));
		}
		// Circle vs Box Collision Check (to be implemented)
		else if (collider1->GetType() == ColliderType::Circle && collider2->GetType() == ColliderType::Box) {
			isCollision = CircleBoxCollision(collider1, static_cast<BoxCollider*>(collider2));
		}
		// Box vs Circle Collision Check (to be implemented)
		else if (collider1->GetType() == ColliderType::Box && collider2->GetType() == ColliderType::Circle) {
			isCollision = CircleBoxCollision(collider2, static_cast<BoxCollider*>(collider1));
		}

		// Handle collision
		if (isCollision) {
			collider1->OnCollisionEnter(collider2);
			collider2->OnCollisionEnter(collider1);
		}
	}
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



bool CollisionSystem::CircleBoxCollision(ICollider* box, ICollider* circle) {
	auto bounds = box->GetBounds();
	Vector2 circleCenter = circle->GetPosition();
	float circleRadius = circle->GetRadius();

	//Find the closest point on the AABB to the circle center
	float closestX = std::max(float(bounds.x), std::min(circleCenter.x, float(bounds.x + bounds.w)));
	float closestY = std::max(float(bounds.y), std::min(circleCenter.y, float(bounds.y + bounds.h)));

	//Calculate the distance between the circle's center and this closest point
	Vector2 closestPoint(closestX, closestY);
	float distanceSquared = (circleCenter - closestPoint).LengthSquared();

	//If the distance is less than the circle's radius, an intersection occurs
	return distanceSquared < (circleRadius * circleRadius);
}


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


void CollisionSystem::ResolveCollision(ICollider* col1, ICollider* col2)
{

}