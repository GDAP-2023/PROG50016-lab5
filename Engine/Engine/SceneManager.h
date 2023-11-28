// @file: SceneManager.h
//
// @brief: Header file for SceneManager, a singleton responsible for handling all scenes, entities, and components.
//
// @author: Divyanshu N Singh (DNS)
// @date: 2023-11-28

#pragma once
#ifndef _SCENE_MANAGER_H_

#include "Scene.h"
#include "Entity.h"

class SceneManager final
{
private:
	DECLARE_SINGLETON(SceneManager);

	const std::string DATA_FILE = "../Assets/SceneManager.json";

	Scene* activeScene = nullptr;

	std::list<Scene*> scenesToBeLoaded;
	std::list<Scene*> loadedScenes;
	std::list<Scene*> scenesToBeUnloaded;

protected:
	void Load();
	void Initialize();

	void PreUpdate();
	void Update();
	void Render();
	void PostUpdate();

	void Destroy();

public:
	Scene* GetActiveScene();
	void SetActiveScene(UUID sceneGUID);

	// Scene-related member functions
	Scene* CreateScene();
	
	Scene* LoadScene(json::JSON&);
	Scene* FindSceneById(int sceneGUID);
	Scene* FindSceneByName();  // No duplicate scenes
	bool RemoveScene(int sceneGUID);

	// Entity-related member functions
	Entity* CreateEntityInActiveScene();
	Entity* CreateEntity(int sceneGUID);
	Entity* FindEntityById(int entityGUID);
	std::list<Entity*> FindEntityByName();  // entities can have same name
	std::list<Entity*> FindEntityWithComponentInActiveScene(std::string componentClassName);
	std::list<Entity*> FindEntityWithComponent(int sceneGUID, std::string componentClassName);
	bool RemoveEntityFromActiveScene(int entityGUID);

	// Component-related member functions
	// none

	friend class Engine;
};

#endif // !_SCENE_MANAGER_H_
