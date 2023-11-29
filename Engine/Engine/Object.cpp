#include "EngineCore.h"
#include "Object.h"

IMPLEMENT_ABSTRACT_CLASS(Object)

Object::Object()
{
	UUID _uid;
	CreateUUID(&_uid);

	uid = GUIDToSTRCODE(_uid);
	guid = GUIDTostring(_uid);
}

void Object::Load(json::JSON& json_component)
{
	// Function to be added
}