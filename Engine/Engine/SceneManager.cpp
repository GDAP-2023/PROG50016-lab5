// @file: SceneManager.cpp
//
// @brief: Cpp file for SceneManager, a singleton responsible for handling all scenes, entities, and components.
//
// @author: Divyanshu N Singh (DNS)
// @date: 2023-11-28

#include "EngineCore.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Load()
{
	std::ifstream inputStream(DATA_FILE);
	std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
	json::JSON sceneManagerJSON = json::JSON::Load(str);

	// Store mapping of scene id to scene path location
	// SceneManager must know about every scene in existance
	THROW_RUNTIME_ERROR(!sceneManagerJSON.hasKey("AllScenes"), "Scene Manager must have GIUD & path data of all available scenes.");
	json::JSON allScenes = sceneManagerJSON["AllScenes"];
	for (json::JSON& sceneInfo : allScenes.ArrayRange())
	{
		if (sceneInfo.hasKey("GUID") && sceneInfo.hasKey("Path"))
		{
			std::string sceneGUID = sceneInfo["GUID"].ToString();
			std::string scenePath = sceneInfo["Path"].ToString();

			STRCODE sceneId = GetHashCode(sceneGUID.c_str());
			stringUIDToFile[sceneId] = scenePath;
		}
	}
	
	// Get the active scene GUID. Convert it to STRCODE
	THROW_RUNTIME_ERROR(!sceneManagerJSON.hasKey("ActiveSceneGUID"), "Scene Manager must have an active scene.");
	activeSceneId = GetHashCode(sceneManagerJSON["ActiveSceneGUID"].ToString().c_str());

	// Load the scenes to be loaded at the beginning of the game
	if (sceneManagerJSON.hasKey("LoadedScenes"))
	{
		json::JSON scenesJSON = sceneManagerJSON["LoadedScenes"];
		for (json::JSON& sceneGuidJSON : scenesJSON.ArrayRange())
		{
			THROW_RUNTIME_ERROR(!sceneGuidJSON.hasKey("GUID"), "A loaded scene must have a GUID.");

			STRCODE sceneID = GetHashCode(sceneGuidJSON["GUID"].ToString().c_str());
			if (stringUIDToFile.find(sceneID) != stringUIDToFile.end())
			{
				// Load up Scene JSON file & send the JSON object to Scene
				std::string sceneFileLocation = "../Assets/" + stringUIDToFile[sceneID];

				std::ifstream sceneInputStream(sceneFileLocation);
				std::string sceneStr((std::istreambuf_iterator<char>(sceneInputStream)), std::istreambuf_iterator<char>());
				json::JSON sceneJSON = json::JSON::Load(sceneStr);

				// Load the scene & track it
				Scene* scene = LoadScene(sceneJSON);

				// If this is the active scene, set it
				if (sceneID == activeSceneId)
				{
					activeScene = scene;
					// active scene has to be enabled, or else it won't update and render
					activeScene->isEnabled = true;
				}
			}
		}
	}
	LOG("Loaded SceneManager: " << scenesToBeLoaded.size() << " scenes loaded from JSON.");
}

/// <summary>
/// Initialize all the loaded scenes.
/// </summary>
void SceneManager::Initialize()
{
	for (Scene* scene : loadedScenes)
	{
		scene->Initialize();
	}
}

/// <summary>
/// Load the scenes to-be-loaded.
/// </summary>
void SceneManager::PreUpdate()
{
	for (Scene* scene : scenesToBeLoaded)
	{
		loadedScenes.push_back(scene);
	}
	scenesToBeLoaded.clear();
	// Check if active scene got modified
	if (toBeSetAsActive != nullptr)
	{
		activeScene = toBeSetAsActive;
		// Active scene must be enabled
		activeScene->isEnabled = true;
		toBeSetAsActive = nullptr;
	}
}

/// <summary>
/// Update all the enabled scenes.
/// </summary>
void SceneManager::Update()
{
	for (Scene* scene : loadedScenes)
	{
		if (scene->isEnabled)
		{
			scene->PreUpdate();
			scene->Update();
			scene->PostUpdate();
		}
	}
}

/// <summary>
/// Unload the scenes to-be-unloaded.
/// </summary>
void SceneManager::PostUpdate()
{
	for (Scene* scene : scenesToBeUnloaded)
	{
		scene->Destroy();
		delete scene;
		loadedScenes.remove(scene);
	}
	scenesToBeUnloaded.clear();
}

void SceneManager::Destroy()
{
	for (Scene* scene : loadedScenes)
	{
		scene->Destroy();
		delete scene;
	}
	loadedScenes.clear();
}

// ------------------------- Scene-related member functions -------------------------

Scene* SceneManager::CreateScene()
{
	// This scene might or might not have a JSON file. Can not add it to stringUIDToFile
	Scene* scene = new Scene();
	return scene;
}

Scene* SceneManager::LoadScene(json::JSON& sceneJSON)
{
	Scene* scene = CreateScene();
	scene->Load(sceneJSON);

	// Loaded scenes automatically get added
	scenesToBeLoaded.push_back(scene);

	return scene;
}

Scene* SceneManager::GetActiveScene()
{
	return activeScene;
}

STRCODE SceneManager::GetActiveSceneId()
{
	return activeScene->uid;
}

bool SceneManager::SetActiveScene(std::string sceneGuid)
{
	STRCODE sceneId = GetHashCode(sceneGuid.c_str());
	return SetActiveScene(sceneId);
}

/// <summary>
/// Set a scene as active scene. This scene must be loaded first.
/// </summary>
/// <param name="sceneId">UID of the Scene</param>
/// <returns></returns>
bool SceneManager::SetActiveScene(STRCODE sceneId)
{
	// Look for the scene in scenesToBeLoaded & loadedScenes
	for (Scene* scene : scenesToBeLoaded)
	{
		if (scene->GetUID() == sceneId)
		{
			toBeSetAsActive = scene;
			return true;
		}
	}
	for (Scene* scene : loadedScenes)
	{
		if (scene->GetUID() == sceneId)
		{
			// Ensure that this scene is not scheduled to be deleted
			auto it = std::find_if(scenesToBeUnloaded.begin(), scenesToBeUnloaded.end(),
								   [sceneId](Scene* sc) {
										return sc->GetUID() == sceneId;
									});
			THROW_RUNTIME_ERROR(it != scenesToBeUnloaded.end(), "Error! Setting a Scene as active which got deleted.");
			toBeSetAsActive = scene;
			return true;
		}
	}
	return false;
}

Scene* SceneManager::FindScene(std::string sceneGuid)
{
	STRCODE sceneId = GetHashCode(sceneGuid.c_str());
	return FindScene(sceneId);
}

/// <summary>
/// Finds a scene among the loaded scenes
/// </summary>
/// <param name="sceneId"></param>
/// <returns></returns>
Scene* SceneManager::FindScene(STRCODE sceneId)
{
	for (Scene* scene : loadedScenes)
	{
		if (scene->GetUID() == sceneId)
		{
			return scene;
		}
	}
	return nullptr;
}

bool SceneManager::UnloadScene(std::string sceneGuid)
{
	STRCODE sceneId = GetHashCode(sceneGuid.c_str());
	return UnloadScene(sceneId);
}

bool SceneManager::UnloadScene(STRCODE sceneId)
{
	// Ensure that user is not trying to remove active scene
	Scene* actualActiveScene = (toBeSetAsActive == nullptr) ? activeScene : toBeSetAsActive;
	if (sceneId == actualActiveScene->GetUID())
		return false;

	for (Scene* scene : loadedScenes)
	{
		if (scene->GetUID() == sceneId)
		{
			scenesToBeUnloaded.push_back(scene);
			return true;
		}
	}
	return false;
}

// ------------------------- Entity-related member functions -------------------------

Entity* SceneManager::CreateEntityInActiveScene()
{
	return activeScene->CreateEntity();
}

Entity* SceneManager::CreateEntity(std::string sceneGuid)
{
	STRCODE sceneId = GetHashCode(sceneGuid.c_str());
	return CreateEntity(sceneId);
}

Entity* SceneManager::CreateEntity(STRCODE sceneId)
{
	for (Scene* scene : loadedScenes)
	{
		if (scene->GetUID() == sceneId)
		{
			return scene->CreateEntity();
		}
	}
	return nullptr;
}

Entity* SceneManager::FindEntity(std::string entityGuid)
{
	return activeScene->FindEntity(entityGuid);
}

Entity* SceneManager::FindEntity(STRCODE entityId)
{
	return activeScene->FindEntity(entityId);
}

std::list<Entity*> SceneManager::FindEntityByName(std::string entityName)
{
	return activeScene->FindEntityByName(entityName);
}

std::list<Entity*> SceneManager::FindEntityWithComponent(std::string componentClassName)
{
	return activeScene->FindEntityWithComponent(componentClassName);
}

bool SceneManager::RemoveEntity(std::string entityGuid)
{
	return activeScene->RemoveEntity(entityGuid);
}

bool SceneManager::RemoveEntity(STRCODE entityId)
{
	return activeScene->RemoveEntity(entityId);
}