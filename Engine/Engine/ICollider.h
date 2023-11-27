#pragma once

#ifndef _ICOLLIDER_H
#define _ICOLLIDER_H

#include "EngineCore.h"

class ICollider
{
private:
	std::string id;

	ICollider();
	~ICollider();

public:

	virtual bool CheckCollision(ICollider) = 0;

};


#endif