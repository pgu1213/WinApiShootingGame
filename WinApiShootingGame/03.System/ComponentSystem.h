#pragma once
#include "IDataProvider.h"

class MainGame;

class ComponentSystem {
protected:
    Entity m_id = -1;
    MainGame* mainGame = nullptr;           // ¿Ã∞… ΩÃ±€≈Ê ¡¢±Ÿ¿∏∑Œ
    function<void()> m_event;
public:
    ComponentSystem() = default;
    virtual ~ComponentSystem() = default;
    virtual void Update() abstract;
    virtual void AddEvent(function<void()> func);
};