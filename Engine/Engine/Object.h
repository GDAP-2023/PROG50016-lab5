#pragma once

#ifndef _OBJECT_H_
#define _OBJECT_H_

class Object
{
	DECLARE_ABSTRACT_BASE_CLASS(Object)

private:
	bool isActive = false;

	std::string name = "";
	std::string guid = 0;
	STRCODE uid = -1;

protected:
	Object();
	Object(std::string _guid) : guid(_guid) { }
	Object(std::string _guid, std::string& _name) : guid(_guid), name(_name) { }
	virtual ~Object() = 0;

	virtual void Initialize() = 0;
	virtual void Destroy() {};

public:
	virtual void Load(json::JSON&) {};

	inline bool IsActive() { return isActive; }
	inline std::string& GetName() { return name; }
	inline std::string Getguid() { return guid; }
	inline STRCODE GetUid() { return uid; }
};

#endif // !_OBJECT_H_
