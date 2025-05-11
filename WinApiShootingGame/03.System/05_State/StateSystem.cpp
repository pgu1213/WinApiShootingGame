#include "../../pch.h"
#include "../ComponentSystem.h"
#include "../../02.Component/State.h"
#include "StateSystem.h"

StateSystem::StateSystem(CObject* owner, State* state)
    : m_state(state) {
    m_owner = owner;
}

StateSystem::~StateSystem() {
    delete m_state;
}

void StateSystem::Init()
{
}

void StateSystem::Update(float _deltaTime) {
    if (m_event)
        m_event();
}

void StateSystem::Render(HDC hdc)
{
}

void StateSystem::TakeDamage(int dmg) {
    m_state->currentHP -= dmg;
}

bool StateSystem::IsDead() const {
    return m_state->currentHP <= 0;
}

const State& StateSystem::GetData() const {
    return *m_state;
}