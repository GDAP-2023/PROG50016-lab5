#pragma once

#ifndef _BOXCOLLIDER_H_
#define _BOXCOLLIDER_H_

#include"EngineCore.h"
#include"ICollider.h"
#include"Component.h"O
#include"CollisionSystem.h"
#include"SDL.h"
class BoxCollider: public ICollider,public Component
{
private:
	SDL_Rect m_rect;

	Component transform;

public:
	BoxCollider();

protected:
	~BoxCollider();
	void Destroy();

public:

	void SetSize(int width, int height);

	CollisionSystem::Vector2 GetPosition() const override;
	ColliderType GetType() const override;

	float GetBroadPhaseRadius() const override;
	bool CheckCollision(ICollider* other);



	void OnCollisionEnter(ICollider* other);
	void OnCollisionStay(ICollider* other);
	void OnCollisionExit(ICollider* other);


};


#endif