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
		//std::cout << "Entity Name: " << name << std::endl;
	}

	if (entityData.hasKey("GUID"))
	{
		guid = entityData["GUID"].ToString();
		uid = GetHashCode(guid.c_str());
	}

	// Load the components
	if (entityData.hasKey("Components"))
	{
		json::JSON componentsJSON = entityData["Components"];

		if (componentsJSON.hasKey("Transform"))
		{
			json::JSON transformJSON = entityData["Transform"];
			transform = (Transform*)CreateComponent("Transform");
			//std::cout << "Transform Component Created" << std::endl;
			transform->Load(transformJSON["ClassData"]);
		}

		for (json::JSON& componentJSON : componentsJSON.ArrayRange())
		{
			std::string componentClassName = componentJSON["ClassName"].ToString();
			Component* component = CreateComponent(componentClassName);
			component->Load(componentJSON["ClassData"]);
			//std::cout<< "Component Created: " << componentClassName << std::endl;
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
		component->Initialize();
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
