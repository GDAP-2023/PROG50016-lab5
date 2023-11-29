#pragma once

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Object.h"

class Component;

class Entity final : public Object
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Entity, Object)

private:
	std::string name = "";

	std::list<Component*> components;
	std::list<Component*> componentsToAdd;
	std::list<Component*> componentsToRemove;

protected:
	Entity() = default;
	Entity(std::string _guid) : Object(_guid) { }
	~Entity() = default;

	void Initialize() override;
	void Load(json::JSON&) override;
	void Update();
	void PreUpdate();
	void PostUpdate();
	void Destroy() override;

public:
	bool HasComponent(std::string componentName);
	Component* const GetComponent(const std::string componentName);
	//void AddComponents(const std::vector<std::string>& _component_list);
	//void AddComponent(Component* _component);
	Component* CreateComponent(std::string componentName);
	bool RemoveComponent(Component* _component);

	friend class Scene;
};

#endif // !_ENTITY_H_