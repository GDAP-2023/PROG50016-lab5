#include "EngineCore.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider():m_rect({0,0,0,0})
{
	CollisionSystem::Instance().AddCollider(this);
}

BoxCollider::~BoxCollider()
{
	CollisionSystem::Instance().RemoveCollider(this);
}

void BoxCollider::Destroy()
{

}

bool BoxCollider::CheckCollision(ICollider* other)
{
	return false;
}

void BoxCollider::SetSize(int width,int height)
{
	m_rect= { x, y,width,height };
}


float BoxCollider::GetBroadPhaseRadius() const
{
	return std::sqrt(m_rect.w*m_rect.w + m_rect.h*m_rect.h);
}




// Called when the collider enters a collision
void BoxCollider::OnCollisionEnter(ICollider* other) {
	// Implement what happens when a collision starts here
}

// Called when the collider stays in collision
void BoxCollider::OnCollisionStay(ICollider* other) {
	// Implement what happens when a collision persists here
}

// Called when the collider exits a collision
void BoxCollider::OnCollisionExit(ICollider* other) {
	// Implement what happens when a collision ends here
}
