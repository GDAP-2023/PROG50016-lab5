#pragma once

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Component.h"
#include "Renderable.h"

class Sprite : public Renderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Sprite, Renderable);

public:
	Sprite();
	~Sprite();

protected:
	void Render() override;
};

#endif