#pragma once

#ifndef _BOXCOLLIDER_H_
#define _BOXCOLLIDER_H_

#include"EngineCore.h"
class BoxCollider
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
	bool CheckCollision(ICollider* other);

	void OnCollisionEnter(ICollider* other);
	void OnCollisionStay(ICollider* other);
	void OnCollisionExit(ICollider* other);

public:

};


#endif