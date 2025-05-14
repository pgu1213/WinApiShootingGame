#pragma once
#include "../01.Object/01.Actor/CActor.h"
#include "IDataProvider.h"
class CActor;

class ComponentSystem {
protected:
    CActor* m_owner;
    function<void()> m_event;
public:
    ComponentSystem() = default;
    virtual ~ComponentSystem() = default;
    virtual void Init() = 0;
    virtual void Update(float _deltaTime) = 0;
    virtual void AddEvent(function<void()> func);
};