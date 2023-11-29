#include "EngineCore.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider():m_rect({0,0,0,0})
{
	int myID = GetId();
	Entity* thisEntity = SceneManager::Get().FindEntityById(myID);
	//transform = thisEntity->GetComponent("Transform");

	CollisionSystem::Instance().AddCollider(this);
}

BoxCollider::~BoxCollider()
{
	CollisionSystem::Instance().RemoveCollider(this);
}

void BoxCollider::Destroy()
{

}

bool BoxCollider::HandleCollision(ICollider* other)
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

ColliderType BoxCollider::GetType() const
{
	return ColliderType::Box;
}

// Called when the collider enters a collision
std::list<Entity*> BoxCollider::OnCollisionEnter(ICollider* other) {
	std::list<Entity*> result;
	return result;
}

// Called when the collider stays in collision
std::list<Entity*> BoxCollider::OnCollisionStay(ICollider* other) {
	std::list<Entity*> result;
	return result;
}

// Called when the collider exits a collision
std::list<Entity*> BoxCollider::OnCollisionExit(ICollider* other) {
	std::list<Entity*> result;
	return result;
}



bool BoxCollider::IsSolid() const
{
	return isSolid;
}
void BoxCollider::SetSolid(bool solid)
{
	isSolid = solid;
}