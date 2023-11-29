#include "EngineCore.h"
#include "Scene.h"

Scene::Scene()
{
	UUID _guid;
	CreateUUID(&_guid);

	uid = GUIDToSTRCODE(_guid);
	guid = GUIDTostring(_guid);
}

Scene::Scene(std::string _guid)
{
	uid = GetHashCode(guid.c_str());
	guid = _guid;
}

Scene::~Scene()
{
}