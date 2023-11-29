#pragma once
#ifndef _SCENE_H_

class Entity;

class Scene
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
	Entity* FindEntityById(int entityGUID);
	std::list<Entity*> FindEntityByName();  // entities can have same name
	std::list<Entity*> FindEntityWithComponent(std::string componentClassName);
	bool RemoveEntity(int entityGUID);

	// Getters
	std::string GetGUID();
	STRCODE GetUID();
	std::string& GetName();

	friend class SceneManager;
};

#endif // !_SCENE_H_
