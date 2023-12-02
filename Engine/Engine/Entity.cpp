#include "EngineCore.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"

IMPLEMENT_DYNAMIC_CLASS(Entity)

Entity::Entity()
{
	// Assign a default value to ensure we always have a transform
	transform = (Transform*)CreateComponent("Transform");
}

Entity::Entity(std::string _guid) : Object(_guid)
{
	// Assign a default value to ensure we always have a transform
	transform = (Transform*)CreateComponent("Transform");
}

void Entity::Initialize()
{
	// Initialize happens before first PreUpdate. So it must be called on componentsToAdd
	LOG(componentsToAdd.size() << " components will be added to this entity.")
	for (Object* component : componentsToAdd)
	{
		((Component*) component)->Initialize();
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
	for (Object* component : components)
	{
		((Component*)component)->Update();
	}
}

void Entity::PreUpdate()
{
	for (Object* component : componentsToAdd)
	{
		components.push_back(component);
	}
	componentsToAdd.clear();
}

void Entity::PostUpdate()
{
	for (Object* component : componentsToRemove)
	{
		components.remove(component);
		delete (Component*)component;
	}
	componentsToRemove.clear();
}

void Entity::Destroy()
{
	for (Object* component : components)
	{
		delete (Component*)component;
	}
	delete transform;
	components.clear();
}

bool Entity::HasComponent(std::string componentClassName)
{
	for (Object* component : components)
	{
		if (component->GetDerivedClassName() == componentClassName)
		{
			return true;
		}
	}
	// In case this runs before PreUpdate, check in componentsToAdd
	for (Object* component : componentsToAdd)
	{
		if (component->GetDerivedClassName() == componentClassName)
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
	for (Object* component : components)
	{
		if (component->GetDerivedClassName() == componentClassName)
		{
			return (Component*)component;
		}
	}
	// If this ran before preUpdate, component would be in componentsToAdd
	for (Object* component : componentsToAdd)
	{
		if (component->GetDerivedClassName() == componentClassName)
		{
			return (Component*)component;
		}
	}
	return nullptr;
}

Component* Entity::CreateComponent(std::string componentClassName)
{
	// Prevent creation of duplicate components
	if (HasComponent(componentClassName))
	{
		return GetComponent(componentClassName);
	}

	// DO NOT typecast to Component* here. Object slicing destroys derived class-specific information
	Object* component = CreateObject(componentClassName.c_str());
	((Component*)component)->ownerEntity = this;
	LOG("Created " << componentClassName << " component.")
	componentsToAdd.push_back(component);
	return (Component*)component;
}

bool Entity::RemoveComponent(Component* _component)
{
	for (Object* component : components)
	{
		if (component->GetUid() == _component->GetUid())
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
