#pragma once

#ifndef _Renderable_H_
#define _Renderable_H_

#include "Component.h"

class Renderable : public Component
{
	DECLARE_ABSTRACT_DERIVED_CLASS(Renderable, Component);

protected:
	Renderable();
	~Renderable();

private:
	virtual void Render() = 0;

	friend class RenderSystem;
};

#endif

