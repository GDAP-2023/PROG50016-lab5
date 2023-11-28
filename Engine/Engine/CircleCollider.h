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


public:
	CircleCollider();
protected:
	~CircleCollider();
	void Destroy();

public:

	void SetRadius(float radius);
	float GetBroadPhaseRadius() const override;
	bool CheckCollision(ICollider* other);
	CollisionSystem::Vector2 GetPosition() const override;


	ColliderType GetType() const override;
	void OnCollisionEnter(ICollider* other);
	void OnCollisionStay(ICollider* other);
    void OnCollisionExit(ICollider* other);



};

#endif
