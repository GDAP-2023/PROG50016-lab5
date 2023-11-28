#pragma once

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Object.h"

class Component : public Object
{
	DECLARE_ABSTRACT_DERIVED_CLASS(Component, Object)

	int value = 0;

public:
	Component();
	~Component() override;

	void Initialize() override;
	virtual void Update();

	friend class Entity;
};

#endif // !_COMPONENT_H_
