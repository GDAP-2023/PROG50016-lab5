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
void CircleCollider::OnCollisionEnter(ICollider* other) {
	// Implement what happens when a collision starts here
}

// Called when the collider stays in collision
void CircleCollider::OnCollisionStay(ICollider* other) {
	// Implement what happens when a collision persists here
}

// Called when the collider exits a collision
void CircleCollider::OnCollisionExit(ICollider* other) {
	// Implement what happens when a collision ends here
}

bool CircleCollider::IsSolid() const
{
	return isSolid;
}
void CircleCollider::SetSolid(bool solid)
{
	isSolid= solid;
}