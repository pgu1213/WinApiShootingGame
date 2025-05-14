#pragma once
#include "../01.Object/00.Default/CObject.h"
#include "IDataProvider.h"
class CObject;

class ComponentSystem {
protected:
    CObject* m_owner;
    function<void()> m_event;
public:
    ComponentSystem() = default;
    virtual ~ComponentSystem() = default;
    virtual void Init() = 0;
    virtual void Update(float _deltaTime) = 0;
    virtual void AddEvent(function<void()> func);
};