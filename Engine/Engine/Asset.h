#pragma once

#ifndef  _A_H_
#define _A_H_

#include <string>

class Asset //:public Object
{

protected:
	
	int GUID;	//#TODO Remove if object has it

	std::string AssetName;

	Asset() {};

	~Asset() {};

};

#endif // ! _A_H_
