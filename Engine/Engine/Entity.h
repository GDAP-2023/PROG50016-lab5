/**
* @class Entity
*
* The Entity class is the base class for all the objects in the game.
* It contains a list of Components and a Transform.
*/
#pragma once

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Object.h"

class Transform;
class Component;

class Entity final : public Object
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Entity, Object)

private:
	Transform* transform = nullptr;

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

	void SetPosition(const Vec2& newPosition);

	/**
	 * @brief Check if the Entity has a Component with the given name
	 *
	 * @param componentName Name of the Component
	 * @return true if the Entity has the Component, false if not
	 */
	bool HasComponent(std::string componentName);

	/**
	 * @brief Add a list of Components by their names to the Entity
	 *
	 * @param _component_list List of Components names
	 */
	void AddComponents(const std::vector<std::string>& _component_list);

	/**
	 * @brief Get a Component from Entity with the given name
	 *
	 * @param componentName Name of the Component
	 * @return Component* if the Entity has the Component, nullptr if not
	 */
	Component* const GetComponent(const std::string componentName);

	/**
	 * @brief Create a single Component by its name
	 *
	 * @param componentName Name of the Component
	 * @return Component* if the Component is successfully created, nullptr if not
	 */
	Component* CreateComponent(std::string componentName);

	/**
	* @brief Remove a Component from the Entity
	*
	* @param _component Component to remove
	* @return true if the Component is successfully removed, false if not
	*/
	bool RemoveComponent(Component* _component);

	/**
	* @brief Get all the Components of the Entity
	*
	* @return a list of Components from the Entity
	*/
	std::list<Component*> GetComponents() const { return components; }

	/**
	* @brief Get the Transform of the Entity
	*
	* @return the transform from the Entity
	*/
	const Transform* GetTransform() { return transform; }

	friend class Scene;
};

#endif // !_ENTITY_H_