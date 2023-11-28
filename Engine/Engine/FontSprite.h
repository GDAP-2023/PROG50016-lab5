#pragma once
#include "Renderable.h"

class FontSprite : public Renderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(FontSprite, Renderable);

public:
	FontSprite() = default;

	void Render() override  {};
};

