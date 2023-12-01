#include "EngineCore.h"
#include "Entity.h"
#include "Component.h"

IMPLEMENT_DYNAMIC_CLASS(Entity)

void Entity::Initialize()
{
	CreateComponent("Transform");
	for (auto component : components)
	{
		component->Initialize();
	}
}

void Entity::Load(json::JSON&)
{
	// Function to be added
}

//
void Entity::AddComponent(Component* component) {
	if (component != nullptr) {
		components.push_back(component);

		// If the entity is already initialized, you might want to initialize the component as well
		// component->Initialize();
	}
}

void Entity::Update()
{
	for (auto component : components)
	{
		component->Update();
	}
}

void Entity::PreUpdate()
{
	for (auto component : componentsToAdd)
	{
		
		components.push_back(component);
		component->Initialize(); //?
	}
	componentsToAdd.clear();
}

void Entity::PostUpdate()
{
	for (auto component : componentsToRemove)
	{
		components.remove(component);
		delete component;
	}
	componentsToRemove.clear();
}

void Entity::Destroy() // destroy other component lists as well?
{
	for (auto component : components)
	{
		delete component;
	}
	components.clear();

	for (auto component : componentsToAdd)
	{
		delete component;
	}
	componentsToAdd.clear();

	for (auto component : componentsToRemove)
	{
		delete component;
	}
	componentsToRemove.clear();
}

bool Entity::HasComponent(std::string componentClassName)
{
	for (auto component : components)
	{
		if (component->GetClassName() == componentClassName)
		{
			return true;
		}
	}
	return false;
}

Component* const Entity::GetComponent(const std::string componentClassName)
{
	for (auto component : components)
	{
		if (component->GetClassName() == componentClassName) 
		{
			return component;
		}
	}
	return nullptr;
}

Component* Entity::CreateComponent(std::string componentClassName)
{
	Component* component = (Component*)CreateObject(componentClassName.c_str());
	//component->owner = this;
	componentsToAdd.push_back(component);
	return component; // is return needed?
}

bool Entity::RemoveComponent(Component* _component)
{
	for (auto component : components)
	{
		if (component == _component)
		{
			componentsToRemove.push_back(component);
			return true;
		}
	}
	return false;
}
