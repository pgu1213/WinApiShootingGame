#include "../../99_Default/pch.h"
#include "../ComponentSystem.h"
#include "../../00_MainGame/MainGame.h"
#include "../00_Transform/TransformSystem.h"
#include "ColliderSystem.h"
#include "../../02_Component/Transform.h"
#include "../../02_Component/Collider.h"

ColliderSystem::ColliderSystem(MainGame* game, Entity id, Collider* collider)
    : m_collider(collider) {
    mainGame = game;
    m_id = id;
}

ColliderSystem::~ColliderSystem() {
    delete m_collider;
}

const Collider& ColliderSystem::GetData() const {
    return *m_collider;
}

void ColliderSystem::Update() {
    if(m_event){
        m_event();
    }
}

void ColliderSystem::SetOnCollisionEvent(std::function<void(Entity)> func) {
    m_onCollision = func;
}

void ColliderSystem::InvokeCollisionEvent(Entity other)const {
    if (m_onCollision) m_onCollision(other);
}