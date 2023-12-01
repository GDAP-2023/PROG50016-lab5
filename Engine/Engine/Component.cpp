#include "EngineCore.h"
#include "Component.h"
#include "Entity.h"

IMPLEMENT_ABSTRACT_CLASS(Component)

//functionality needs to be added

Component::Component() : ownerEntity(nullptr)
{
}

Component::~Component()
{
}

void Component::Initialize()
{
}

void Component::Load(json::JSON& node)
{
    //needs to be added
}

void Component::SetOwner(Entity* owner)
{
    ownerEntity = owner;
}

Entity* Component::GetOwner() const
{
    return ownerEntity;
}

void Component::Update() {

}
