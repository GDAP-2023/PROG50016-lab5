#pragma once

#ifndef _BOXCOLLIDER_H_
#define _BOXCOLLIDER_H_

#include"EngineCore.h"
#include"ICollider.h"
#include"Component.h"
#include"CollisionSystem.h"
class BoxCollider: public ICollider,public Component
{
private:
	SDL_Rect m_rect;


public:
	BoxCollider();

protected:
	~BoxCollider();
	void Destroy();

public:

	void SetSize(int width, int height);
	Vector2 GetPosition() const override;
	float GetBroadPhaseRadius() const override;
	bool CheckCollision(ICollider* other);


	void OnCollisionEnter(ICollider* other);
	void OnCollisionStay(ICollider* other);
	void OnCollisionExit(ICollider* other);


};


#endif