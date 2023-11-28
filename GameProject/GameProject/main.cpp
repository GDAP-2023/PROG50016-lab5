#include "GameCore.h"

#include <string>
//#include <rpcdce.h>

int main()
{
	UUID _uid;
	CreateUUID(&_uid);

	unsigned int uid = GUIDToSTRCODE(_uid);
	std::string guid = GUIDTostring(_uid);

	/*std::string guid = GUIDTostring(_uid);*/

	Engine::Instance().Initialize();
	Engine::Instance().GameLoop();
	Engine::Instance().Destroy();
}
