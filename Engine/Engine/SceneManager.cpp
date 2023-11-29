// @file: SceneManager.cpp
//
// @brief: Cpp file for SceneManager, a singleton responsible for handling all scenes, entities, and components.
//
// @author: Divyanshu N Singh (DNS)
// @date: 2023-11-28

#include "EngineCore.h"
#include "SceneManager.h"

void SceneManager::Load()
{
	std::ifstream inputStream(DATA_FILE);
	std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
	json::JSON sceneManagerJSON = json::JSON::Load(str);

	THROW_RUNTIME_ERROR(!sceneManagerJSON.hasKey("GUIDtoSceneMap"), "Scene Manager must have GUID to filename mapping for each scene.");
	json::JSON guidToSceneFile = sceneManagerJSON["GUIDtoSceneMap"];

	// TODO: Scene Manager should keep track of all the available scenes, even the ones which are not loaded

	// Get the active scene GUID
	THROW_RUNTIME_ERROR(!sceneManagerJSON.hasKey("ActiveSceneGUID"), "Scene Manager must have an active scene.");
	std::string activeSceneGUID = sceneManagerJSON["ActiveSceneGUID"].ToString();

	// Load the scenes to be loaded at the beginning of the game
	if (sceneManagerJSON.hasKey("LoadedScenes"))
	{
		json::JSON scenesJSON = sceneManagerJSON["LoadedScenes"];
		for (json::JSON& sceneGuidJSON : scenesJSON.ArrayRange())
		{
			THROW_RUNTIME_ERROR(!sceneGuidJSON.hasKey("SceneGUID"), "Loaded scenes must have a GUID.");

			std::string sceneGUID = sceneGuidJSON["SceneGUID"].ToString();
			if (guidToSceneFile.hasKey(sceneGUID))
			{
				// Load up Scene JSON file & send the JSON object to Scene
				std::string sceneFileLocation = "../Assets/" + guidToSceneFile[sceneGUID].ToString();

				std::ifstream sceneInputStream(sceneFileLocation);
				std::string sceneStr((std::istreambuf_iterator<char>(sceneInputStream)), std::istreambuf_iterator<char>());
				json::JSON sceneJSON = json::JSON::Load(sceneStr);

				Scene* scene = LoadScene(sceneJSON);
				loadedScenes.push_back(scene);

				// If this is the active scene, set it
				if (sceneGUID == activeSceneGUID)
				{
					activeScene = scene;
					// active scene has to be enabled, or else it won't update and render
					activeScene->isEnabled = true;
				}
			}
		}
	}
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
		scene->Initialize();
		loadedScenes.push_back(scene);
	}
	scenesToBeLoaded.clear();
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
			scene->Update();
		}
	}
}

/// <summary>
/// Render all the enabled scenes.
/// </summary>
void SceneManager::Render()
{
	for (Scene* scene : loadedScenes)
	{
		if (scene->isEnabled)
		{
			scene->Render();
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
		loadedScenes.remove(scene);
	}
	scenesToBeUnloaded.clear();
}

void SceneManager::Destroy()
{
	for (Scene* scene : loadedScenes)
	{
		scene->Destroy();
	}
	loadedScenes.clear();
}

Scene* SceneManager::GetActiveScene()
{
	return activeScene;
}

void SetActiveScene(UUID sceneGUID)
{
}

Scene* SceneManager::CreateScene()
{
	Scene* scene = new Scene();
	
	// TODO: Create the meta file for this scene
	
	// TODO: SceneManager must keep track of all the created scenes
	// Maybe via a map?

	return scene;
}

Scene* SceneManager::LoadScene(json::JSON& sceneJSON)
{
	Scene* scene = CreateScene();
	scene->Load(sceneJSON);

	return scene;
}
