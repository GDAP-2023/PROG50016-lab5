#include "EngineCore.h"

#include "Object.h"
#include "Component.h"
#include "Renderable.h"
#include "FontSprite.h"
#include "AnimatedSprite.h"

void Engine_Register()
{
	REGISTER_TYPECLASS(Object);
	REGISTER_TYPECLASS(Component);
	REGISTER_TYPECLASS(Renderable);
	REGISTER_TYPECLASS(FontSprite);
	REGISTER_TYPECLASS(AnimatedSprite);
}
