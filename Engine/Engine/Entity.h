/**
* @class Entity
*
* Detailed description, including the purpose and usage of the class.
*/
#pragma once

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Object.h"

class Component;

class Entity final : public Object
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Entity, Object)

private:
	Transform transform;

	std::list<Component*> components;
	std::list<Component*> componentsToAdd;
	std::list<Component*> componentsToRemove;

protected:
	Entity() = default;
	Entity(std::string _guid) : Object(_guid) { }
	~Entity() = default;

	void Initialize() override;
	void Load(json::JSON& _entityJSON) override;
	void Update();
	void PreUpdate();
	void PostUpdate();
	void Destroy() override;

public:
	/**
	 * @brief Check if the Entity has a Component with the given name
	 *
	 * @param componentName Description of the first parameter.
	 * @return Description of the return value.
	 */
	bool HasComponent(std::string componentName);

	/**
	 * @brief Add a list of Components by their names to the Entity
	 *
	 * @param _component_list Description of the first parameter.
	 * @return Description of the return value.
	 */
	void AddComponents(const std::vector<std::string>& _component_list);

	/**
	 * @brief Get a Component from Entity with the given name
	 *
	 * @param componentName Description of the first parameter.
	 * @return Description of the return value.
	 */
	Component* const GetComponent(const std::string componentName);

	/**
	 * @brief Create a single Component by its name
	 *
	 * @param componentName Description of the first parameter.
	 * @return Description of the return value.
	 */
	Component* CreateComponent(std::string componentName);

	/**
	* @brief Remove a Component from the Entity
	*
	* @param _component Description of the first parameter.
	* @return Description of the return value.
	*/
	bool RemoveComponent(Component* _component);

	/**
	* @brief Get all the Components of the Entity
	*
	* @return Description of the return value.
	*/
	std::list<Component*> GetComponents() const { return components; }

	Transform* GetTransform() const { return transform; }

	friend class Scene;
};

#endif // !_ENTITY_H_