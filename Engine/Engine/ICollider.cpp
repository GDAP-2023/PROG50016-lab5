#include "EngineCore.h"

#include "ICollider.h"

IMPLEMENT_ABSTRACT_CLASS(ICollider);

ICollider::ICollider()
{

}

ICollider::~ICollider()
{

}

void ICollider::StorePosition(Vec2 position)
{
	previousPosition = position;
}

void ICollider::ResetPosition()
{
	//TODO: RestPosition
	
}
