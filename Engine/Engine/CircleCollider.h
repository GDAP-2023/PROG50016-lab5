#pragma once
#ifndef _CIRCLECOLLIDER_H_
#define _CIRCLECOLLIDER_H_

#include"EngineCore.h"
class CircleCollider
{
private:
	float m_radius;


public:
	CircleCollider();
protected:
	~CircleCollider();
	void Destory();

public:
	bool CheckCollision(ICollider* other);
	void SetRadius(float radius);

	void OnCollisionEnter(ICollider* other);
	void OnCollisionStay(ICollider* other);
    void OnCollisionExit(ICollider* other);

};

#endif
