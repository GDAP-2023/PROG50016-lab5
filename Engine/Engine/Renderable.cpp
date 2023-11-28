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
