#include "EngineCore.h"
#include "Renderable.h"
#include "RenderSystem.h"

IMPLEMENT_ABSTRACT_CLASS(Renderable)

Renderable::Renderable()
{
	RenderSystem::Instance().AddRenderable(this);
}

Renderable::~Renderable()
{
	RenderSystem::Instance().RemoveRenderable(this);
}

/*
* User enters 4 int values to form RGB and Alpha. Nothing clamps the values so positive values
* and negative values will loop in their respective directions. 
*/
void Renderable::SetFilterColor(int r, int g, int b, int a)
{
	_filterColor.r = r;
	_filterColor.g = g;
	_filterColor.b = b;
	_filterColor.a = a;
}
