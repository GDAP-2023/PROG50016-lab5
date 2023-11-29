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
	friend class Engine;
	DECLARE_SINGLETON(SceneManager);

	const std::string DATA_FILE = "../Assets/SceneManager.json";

	STRCODE activeSceneId = 0;
	Scene* activeScene = nullptr;

	// Scene to be set as active (happens in pre-update)
	Scene* toBeSetAsActive = nullptr;

	std::list<Scene*> scenesToBeLoaded;
	std::list<Scene*> loadedScenes;
	std::list<Scene*> scenesToBeUnloaded;

	// Keep track of file location for each Scene available
	// (i.e. a scene which either has a JSON or got created by user during runtime)
	std::map <STRCODE, std::string> stringUIDToFile;

protected:
	void Load();
	void Initialize();

	void PreUpdate();
	void Update();
	void Render();
	void PostUpdate();

	void Destroy();

public:
	// ------------------------- Scene-related member functions -------------------------
	Scene* GetActiveScene();
	STRCODE GetActiveSceneId();
	bool SetActiveScene(std::string sceneGuid);
	bool SetActiveScene(STRCODE sceneId);

	Scene* CreateScene();
	
	Scene* LoadScene(json::JSON&);
	Scene* FindScene(std::string sceneGuid);
	Scene* FindScene(STRCODE sceneId);
	bool UnloadScene(std::string sceneGuid);
	bool UnloadScene(STRCODE sceneId);

	// ------------------------- Entity-related member functions -------------------------
	Entity* CreateEntityInActiveScene();
	Entity* CreateEntity(int sceneGUID);
	Entity* FindEntityById(int entityGUID);
	std::list<Entity*> FindEntityByName();  // entities can have same name
	std::list<Entity*> FindEntityWithComponentInActiveScene(std::string componentClassName);
	std::list<Entity*> FindEntityWithComponent(int sceneGUID, std::string componentClassName);
	bool RemoveEntityFromActiveScene(int entityGUID);
};

#endif // !_SCENE_MANAGER_H_
