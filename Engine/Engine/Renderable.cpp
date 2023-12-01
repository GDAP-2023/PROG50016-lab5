/*
* @Renderable
*
* Abstract class that any component that needs to be renderered to the RenderSystems
* SDL Window inherits from. Allows the user to pick a color filter to set over any
* Sprites.
*/

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
* @SetFilterColor
*
* Allows the user to set a color filter that will be applied overtop of their sprite.
* Takes RGB Values along with an Alpha. Nothing clamps the values so numbers bigger then 255
* or less than 0 will loop in their respective directions.
*/
void Renderable::SetFilterColor(int r, int g, int b, int a)
{
	_filterColor.r = r;
	_filterColor.g = g;
	_filterColor.b = b;
	_filterColor.a = a;
}
