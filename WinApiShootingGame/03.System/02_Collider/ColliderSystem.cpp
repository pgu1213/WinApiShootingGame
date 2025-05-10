#include "../../pch.h"
#include "../ComponentSystem.h"
#include "ColliderSystem.h"
#include "../../02.Component/Collider.h"

ColliderSystem::ColliderSystem(CObject* owner, Collider* collider)
    : m_collider(collider) {
    m_owner = owner;
}

ColliderSystem::~ColliderSystem() {
    delete m_collider;
}

const Collider& ColliderSystem::GetData() const {
    return *m_collider;
}

void ColliderSystem::Update(float _deltaTime) {
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