#pragma once

#ifndef _OBJECT_H_
#define _OBJECT_H_

class Object
{
    DECLARE_ABSTRACT_BASE_CLASS(Object)

protected:
    bool isActive = false;

    std::string name;
    std::string guid;
    STRCODE uid = -1;

protected:
    Object();
    explicit Object(std::string guid);
    Object(std::string guid, std::string name);
    virtual ~Object() = default;

    virtual void Initialize() = 0;
    virtual void Destroy() {}

public:
    virtual void Load(json::JSON&);

    bool IsActive() const { return isActive; }
    std::string& GetName() { return name; }
    std::string& GetGuid() { return guid; }
    STRCODE GetUid() const { return uid; }
};

#endif // !_OBJECT_H_
