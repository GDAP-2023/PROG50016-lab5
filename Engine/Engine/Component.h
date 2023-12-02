#pragma once

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Object.h"

class Entity;

class Component : public Object
{
    DECLARE_ABSTRACT_DERIVED_CLASS(Component, Object)

protected:
    Entity* ownerEntity;

public:
    Component();
    virtual ~Component() override;

    virtual void Initialize() override;
    //change to pure virtual function
    virtual void Update() = 0;
    virtual void Load(json::JSON& node) override;
    virtual void Render() {}; // Are some components going to need to render?

    void SetOwner(Entity* owner);
    Entity* GetOwner() const;

    friend class Entity; // To allow Entity to access protected/private members
};

#endif // !_COMPONENT_H_
