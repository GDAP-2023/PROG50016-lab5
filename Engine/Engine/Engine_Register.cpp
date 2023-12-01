#include "EngineCore.h"

#include "Object.h"
#include "Component.h"
#include "Renderable.h"
#include "FontSprite.h"
#include "AnimatedSprite.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "ICollider.h"

void Engine_Register()
{
	REGISTER_TYPECLASS(Object);
	REGISTER_TYPECLASS(Component);
	REGISTER_TYPECLASS(Renderable);
	REGISTER_TYPECLASS(FontSprite);
	REGISTER_TYPECLASS(AnimatedSprite);
	REGISTER_TYPECLASS(CircleCollider);
	REGISTER_TYPECLASS(BoxCollider);
	REGISTER_TYPECLASS(ICollider);
}
