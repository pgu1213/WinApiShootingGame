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
    virtual void Init() abstract;
    virtual void Update(float _deltaTime) abstract;
	virtual void Render(HDC hdc) abstract;
    virtual void AddEvent(function<void()> func);
};