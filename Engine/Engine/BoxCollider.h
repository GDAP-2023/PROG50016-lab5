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
	bool isSolid = false;
	Component transform;

public:
	BoxCollider();

protected:
	~BoxCollider();
	void Destroy();

public:

	void SetSize(int width, int height);

	Vec2 GetPosition() const override;
	ColliderType GetType() const override;

	virtual bool IsSolid() const = 0;
	virtual void SetSolid(bool solid) = 0;

	float GetBroadPhaseRadius() const override;
	bool HandleCollision(ICollider* other);



	std::list<Entity*> OnCollisionEnter(ICollider* other);
	std::list<Entity*> OnCollisionStay(ICollider* other);
	std::list<Entity*> OnCollisionExit(ICollider* other);


};


#endif