#pragma once
#ifndef _SCENE_H_

class Entity;

class Scene
{
private:
	std::list<Entity*> entities;
	std::string name = "";
	int guid = 0;

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

	Entity* CreateEntity();
	Entity* FindEntityById(int entityGUID);
	std::list<Entity*> FindEntityByName();  // entities can have same name
	std::list<Entity*> FindEntityWithComponent(std::string componentClassName);
	bool RemoveEntity(int entityGUID);

	std::string& GetName();
	int GetGUID();

	friend class SceneManager;
};

#endif // !_SCENE_H_
