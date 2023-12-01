#pragma once

#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include "Component.h"
#include "SDL.h"

class Renderable : public Component
{
	friend class RenderSystem;

	DECLARE_ABSTRACT_DERIVED_CLASS(Renderable, Component);

	void SetFilterColor(int r, int g, int b, int a);

	virtual void Render() = 0;

protected:

	SDL_Color _filterColor = { 255, 255, 255 };

	Renderable();

	~Renderable();
};

#endif

