// @file: Scene.h
//
// @brief: Header file for the Scene class. All entities are part of a Scene.
//
// @author: Divyanshu N Singh (DNS)
// @date: 2023-11-29

#pragma once
#ifndef _SCENE_H_

class Entity;

class Scene final
{
private:
	std::string guid = "";
	STRCODE uid = 0;
	std::string name = "";


	std::list<Entity*> entities;
	std::list<Entity*> entitiesToDestroy;

protected:
	void Initialize();
	void Load(json::JSON&);

	void Update();
	void Render();
	void PostUpdate();

	void Destroy();

public:
	// Only enabled scenes get updated & rendered
	bool isEnabled = true;

	Scene();
	Scene(std::string guid);
	~Scene();

	Entity* CreateEntity();
	Entity* FindEntity(std::string entityGuid);
	Entity* FindEntity(STRCODE entityId);
	std::list<Entity*> FindEntityByName(std::string entityName);  // entities can have same name
	std::list<Entity*> FindEntityWithComponent(std::string componentClassName);
	bool RemoveEntity(std::string entityGuid);
	bool RemoveEntity(STRCODE entityId);

	// Getters
	std::string& GetGUID();
	STRCODE GetUID();
	std::string& GetName();

	friend class SceneManager;
};

#endif // !_SCENE_H_
