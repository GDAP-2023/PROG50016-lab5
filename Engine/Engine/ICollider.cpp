#include "EngineCore.h"

#include "ICollider.h"

ICollider::ICollider()
{

}

ICollider::~ICollider()
{

}

void ICollider::StorePosition(Vector2 position)
{
	previousPosition = position;
}

void ICollider::ResetPosition()
{
	//TODO: RestPosition
	
}
