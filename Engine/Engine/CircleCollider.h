#pragma once
#ifndef _CIRCLECOLLIDER_H_
#define _CIRCLECOLLIDER_H_

#include"EngineCore.h"
#include"ICollider.h"
#include"Component.h"
#include"CollisionSystem.h"

class CircleCollider : public ICollider, public Component
{
private:
	float m_radius;
	bool isSolid = false;
public:
	CircleCollider();
protected:
	~CircleCollider();
	void Destroy();

public:

	void SetRadius(float radius);
	float GetBroadPhaseRadius() const override;

	virtual bool IsSolid() const = 0;
	virtual void SetSolid(bool solid) = 0;

	bool HandleCollision(ICollider* other);
	Vec2 GetPosition() const override;


	ColliderType GetType() const override;
	std::list<Entity*> OnCollisionEnter(ICollider* other);
	std::list<Entity*> OnCollisionStay(ICollider* other);
	std::list<Entity*> OnCollisionExit(ICollider* other);



};

#endif
