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

	bool CheckCollision(ICollider* other);

	void SetRadius(float radius);

	void OnCollisionEnter(ICollider* other);

	void OnCollisionStay(ICollider* other);

    void OnCollisionExit(ICollider* other);

};

#endif
