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
	auto potentialCollisions = BroadPhaseDetection();
	auto currentFrameCollisions = NarrowPhaseDetection(potentialCollisions);

	std::set<std::pair<ICollider*, ICollider*>> collisionsToRemove;

	//flush exit and stay lists
	enterCollisions.clear();
	exitCollisions.clear();

	// Handle new and ongoing collisions
	for (const auto& collisionPair : currentFrameCollisions)
	{
		if (collisionPair.first->IsSolid() && collisionPair.second->IsSolid())
		{
			ResolveCollision(collisionPair.first, collisionPair.second);
		}
		else 
		{
			if (ongoingCollisions.find(collisionPair) == ongoingCollisions.end()) 
			{
				// New collision
				//not sure if these next two lines are code with our new implementation of OnEnter/Stay/Exit
				collisionPair.first->OnCollisionEnter(collisionPair.second);
				collisionPair.second->OnCollisionEnter(collisionPair.first);
				enterCollisions.push_back(collisionPair);
			}
			else 
			{
				// Ongoing collision
				collisionPair.first->OnCollisionStay(collisionPair.second);
				collisionPair.second->OnCollisionStay(collisionPair.first);
				stayCollisions.push_back(collisionPair);
			}
		}
	}

	// Determine which collisions have ended
	for (const auto& oldCollision : ongoingCollisions) 
	{
		if (currentFrameCollisions.find(oldCollision) == currentFrameCollisions.end()) 
		{
			collisionsToRemove.insert(oldCollision);
			oldCollision.first->OnCollisionExit(oldCollision.second);
			oldCollision.second->OnCollisionExit(oldCollision.first);
			exitCollisions.push_back(oldCollision);
			//flush this pair from the stay list
			bool inList = std::find(stayCollisions.begin(), stayCollisions.end(), oldCollision) != stayCollisions.end();
			if (inList) { stayCollisions.remove(oldCollision); }
		}
	}

	// Remove ended collisions from ongoing collisions
	for (const auto& collisionToRemove : collisionsToRemove) 
	{
		ongoingCollisions.erase(collisionToRemove);
	}

	// Update ongoing collisions for the next frame
	ongoingCollisions = std::move(currentFrameCollisions);

}

void CollisionSystem::AddCollider(ICollider* collider)
{
	colliders.push_back(collider);
}

void CollisionSystem::RemoveCollider(ICollider* collider)
{
	colliders.remove(collider);
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

			Vec2 position1 = collider1->GetPosition();
			Vec2 position2 = collider2->GetPosition();

			Vec2 positionDiff = position1 - position2;
			float radiusSum = radius1 + radius2;
			if(positionDiff.MagnitudeSquared()<= (radiusSum * radiusSum))
			{
				potentialCollisions.push_back(std::make_pair(collider1, collider2));
			}
		}
	}

	return potentialCollisions;
}


std::set<std::pair<ICollider*, ICollider*>> CollisionSystem::NarrowPhaseDetection(const std::list<std::pair<ICollider*, ICollider*>>& potentialCollisions) {
	
	std::set<std::pair<ICollider*, ICollider*>> currentFrameCollisions;

	for (const auto& collisionPair : potentialCollisions) {
		ICollider* collider1 = collisionPair.first;
		ICollider* collider2 = collisionPair.second;

		bool isCollision = false;

		// Circle vs Circle Collision Check
		if (collider1->GetType() == ColliderType::Circle && collider2->GetType() == ColliderType::Circle) 
		{
			isCollision = CircleCircleCollision(static_cast<CircleCollider*>(collider1), static_cast<CircleCollider*>(collider2));
		}
		// Box vs Box Collision Check (to be implemented)
		else if (collider1->GetType() == ColliderType::Box && collider2->GetType() == ColliderType::Box)
		{
			isCollision = BoxBoxCollision(static_cast<BoxCollider*>(collider1), static_cast<BoxCollider*>(collider2));
		}
		// Circle vs Box Collision Check (to be implemented)
		else if (collider1->GetType() == ColliderType::Circle && collider2->GetType() == ColliderType::Box) 
		{
			isCollision = CircleBoxCollision(collider1, static_cast<BoxCollider*>(collider2));
		}
		// Box vs Circle Collision Check (to be implemented)
		else if (collider1->GetType() == ColliderType::Box && collider2->GetType() == ColliderType::Circle) 
		{
			isCollision = CircleBoxCollision(collider2, static_cast<BoxCollider*>(collider1));
		}

		// Handle collision
		if (isCollision)
		{
			currentFrameCollisions.insert(collisionPair);
		}
	}
	return currentFrameCollisions;
}






// Helper function for calculating distance between two points
float DistanceSquared(const Vec2& a, const Vec2& b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return dx * dx + dy * dy;
}

// Helper function for Circle-Circle collision
bool CollisionSystem::CircleCircleCollision(ICollider* col1, ICollider* col2) {
	CircleCollider* circle1 = (CircleCollider*)col1;
	CircleCollider* circle2 = (CircleCollider*)col2;
	Vec2 positionDiff = circle1->GetPosition() - circle2->GetPosition();
	float radiusSum = circle1->GetRadius() + circle2->GetRadius();
	return positionDiff.MagnitudeSquared() <= (radiusSum * radiusSum);
}

// Helper function for Box-Box collision using AABB (Axis-Aligned Bounding Box)
bool CollisionSystem::BoxBoxCollision(ICollider* col1, ICollider* col2) {
	BoxCollider* box1 = (BoxCollider*)col1;
	BoxCollider* box2 = (BoxCollider*)col2;
	auto bounds1 = box1->GetBounds();
	auto bounds2 = box2->GetBounds();

	// Check if one box is to the left of the other or above the other
	return !(bounds1.x + bounds1.w < bounds2.x || bounds2.x + bounds2.w < bounds1.x ||
		bounds1.y + bounds1.h < bounds2.y || bounds2.y + bounds2.h < bounds1.y);
}


// Helper function for Circle-Box collision using AABB (Axis-Aligned Bounding Box)
bool CollisionSystem::CircleBoxCollision(ICollider* col1, ICollider* col2) {
	BoxCollider* box = (BoxCollider*)col1;
	CircleCollider* circle = (CircleCollider*)col2;
	auto bounds = box->GetBounds();
	Vec2 circleCenter = circle->GetPosition();
	float circleRadius = circle->GetRadius();

	//Find the closest point on the AABB to the circle center
	float closestX = std::max(float(bounds.x), std::min(circleCenter.x, float(bounds.x + bounds.w)));
	float closestY = std::max(float(bounds.y), std::min(circleCenter.y, float(bounds.y + bounds.h)));

	//Calculate the distance between the circle's center and this closest point
	Vec2 closestPoint(closestX, closestY);
	float distanceSquared = (circleCenter - closestPoint).MagnitudeSquared();

	//If the distance is less than the circle's radius, an intersection occurs
	return distanceSquared < (circleRadius * circleRadius);
}



void CollisionSystem::ResolveCollision(ICollider* col1, ICollider* col2)
{
	// Both colliders are solid, revert to previous positions
	col1->ResetPosition();
	col2->ResetPosition();
	//reset position not implemented, causing errors when we call it here
}

//void CollisionSystem::ResolveCollision(ICollider* col1, ICollider* col2)
//{
//	col1->HandleCollision(col2);
//	col2->HandleCollision(col1);
//}