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

void ColliderSystem::Init()
{
}

const Collider& ColliderSystem::GetData() const {
    return *m_collider;
}

void ColliderSystem::Update(float _deltaTime) {
    if(m_event){
        m_event();
    }
}

void ColliderSystem::Render(HDC hdc)
{
}

void ColliderSystem::SetOnCollisionEvent(std::function<void(CObject*)> func) {
    m_onCollision = func;
}

void ColliderSystem::InvokeCollisionEvent(CObject* other)const {
    if (m_onCollision) m_onCollision(other);
}