#include "EngineCore.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"

IMPLEMENT_DYNAMIC_CLASS(Entity)

void Entity::Initialize()
{
	transform = (Transform*)CreateComponent("Transform");

	for (auto component : components)
	{
		component->Initialize();
	}
}

void Entity::Load(json::JSON& entityData)
{
	if (entityData.hasKey("Name"))
	{
		name = entityData["Name"].ToString();
	}

	if (entityData.hasKey("GUID"))
	{
		guid = entityData["GUID"].ToString();
		uid = GetHashCode(guid.c_str());
	}

	// Load the transform (necessary component of any entity)
	// Not throwing runtime error because if there is no transform, we assign a default one during initialize
	if (entityData.hasKey("Transform"))
	{
		transform = (Transform*) CreateComponent("Transform");
		transform->Load(entityData["Transform"]);
		LOG("Loaded up transform in entity " << name)
	}

	// Load the components
	if (entityData.hasKey("Components"))
	{
		for (json::JSON& componentJSON : entityData["Components"].ArrayRange())
		{
			std::string componentClassName = componentJSON["ClassName"].ToString();
			Component* component = CreateComponent(componentClassName);
			component->Load(componentJSON["ClassData"]);
			LOG("Loaded up component " << componentClassName << " in entity " << name)
		}
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

void Entity::Destroy()
{
	for (auto component : components)
	{
		delete component;
	}
	delete transform;
	components.clear();
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

void Entity::AddComponents(const std::vector<std::string>& _component_list)
{
	for (std::string component : _component_list)
	{
		CreateComponent(component);
	}
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
	component->ownerEntity = this;
	componentsToAdd.push_back(component);
	return component;
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

void Entity::SetPosition(const Vec2& newPosition) {
	if (transform) {
		transform->position = newPosition;
	}
}
