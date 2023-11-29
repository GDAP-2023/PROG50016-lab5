// @file: Scene.cpp
//
// @brief: Cpp file for the Scene class. All entities are part of a Scene.
//
// @author: Divyanshu N Singh (DNS)
// @date: 2023-11-29

#include "EngineCore.h"
#include "Scene.h"
#include "Entity.h"

Scene::Scene()
{
	UUID _guid;
	// Create a new GUID
	CreateUUID(&_guid);

	guid = GUIDTostring(_guid);
	uid = GetHashCode(guid.c_str());
}

Scene::Scene(std::string _guid)
{
	// Use the GUID passed to it
	uid = GetHashCode(guid.c_str());
	guid = _guid;
}

Scene::~Scene()
{
}

void Scene::Initialize()
{
}

void Scene::Load(json::JSON& sceneJSON)
{
	THROW_RUNTIME_ERROR(!sceneJSON.hasKey("AssetManager"), "Scene JSON must contain GUIDs of all the assets it needs.");
	THROW_RUNTIME_ERROR(!sceneJSON.hasKey("Scene"), "Scene JSON must contain scene info.");

	// TODO: Pass sceneJSON["AssetManager"] json to AssetManager

	json::JSON sceneData = sceneJSON["Scene"];
	if (sceneData.hasKey("Name"))
	{
		name = sceneData["Name"].ToString();
	}
	// If GUID exists, it overwrites the guid & uid populated in Scene constructor
	if (sceneData.hasKey("GUID"))
	{
		guid = sceneData["GUID"].ToString();
		uid = GetHashCode(guid.c_str());
	}
	if (sceneData.hasKey("IsEnabled"))
	{
		isEnabled = sceneData["IsEnabled"].ToBool();
	}

	// Load the entities
	if (sceneData.hasKey("Entities"))
	{
		json::JSON entitiesJSON = sceneData["Entities"];
		for (json::JSON& entityJSON : entitiesJSON.ArrayRange())
		{
			Entity* entity = CreateEntity();
			entity->Load(entityJSON);
		}
	}
}

void Scene::PreUpdate()
{
	for (Entity* entity : entitiesToBeAdded)
	{
		entities.push_back(entity);
	}
	entitiesToBeAdded.clear();
}

void Scene::Update()
{
	for (Entity* entity : entities)
	{
		if (entity->IsActive())
		{
			entity->PreUpdate();
			entity->Update();
			entity->PostUpdate();
		}
	}
}

void Scene::PostUpdate()
{
	for (Entity* entity : entitiesToDestroy)
	{
		entity->Destroy();
		delete entity;
		entities.remove(entity);
	}
	entitiesToDestroy.clear();
}

void Scene::Destroy()
{
	for (Entity* entity : entities)
	{
		entity->Destroy();
		delete entity;
	}
	entities.clear();
}

Entity* Scene::CreateEntity()
{
	Entity* entity = new Entity();
	// The scene that creates an entity has its ownership
	entitiesToBeAdded.push_back(entity);
	return entity;
}

Entity* Scene::FindEntity(std::string entityGuid)
{
	STRCODE entityId = GetHashCode(entityGuid.c_str());
	return FindEntity(entityId);
}

Entity* Scene::FindEntity(STRCODE entityId)
{
	for (Entity* entity : entities)
	{
		if (entity->GetUid() == entityId)
		{
			return entity;
		}
	}
	return nullptr;
}

std::list<Entity*> Scene::FindEntityByName(std::string entityName)
{
	std::list<Entity*> foundEntities;
	for (Entity* entity : entities)
	{
		if (entity->GetName() == entityName)
		{
			foundEntities.push_back(entity);
		}
	}
	return foundEntities;
}

std::list<Entity*> Scene::FindEntityWithComponent(std::string componentName)
{
	std::list<Entity*> foundEntities;
	for (Entity* entity : entities)
	{
		if (entity->GetComponent(componentName))
		{
			foundEntities.push_back(entity);
		}
	}
	return foundEntities;
}

bool Scene::RemoveEntity(std::string entityGuid)
{
	STRCODE entityId = GetHashCode(entityGuid.c_str());
	return RemoveEntity(entityId);
}

bool Scene::RemoveEntity(STRCODE entityId)
{
	for (Entity* entity : entities)
	{
		if (entity->GetUid() == entityId)
		{
			entitiesToDestroy.push_back(entity);
			return true;
		}
	}
	return false;
}

// ------------------------- Getters -------------------------

std::string& Scene::GetGUID()
{
	return guid;
}

STRCODE Scene::GetUID()
{
	return uid;
}

std::string& Scene::GetName()
{
	return name;
}

