#include "../../pch.h"
#include "../ComponentSystem.h"
#include "../../02.Component/State.h"
#include "StateSystem.h"

StateSystem::StateSystem(MainGame* game, Entity id, State* state)
    : m_state(state) {
    mainGame = game;
    m_id = id;
}

StateSystem::~StateSystem() {
    delete m_state;
}

void StateSystem::Update() {
    if (m_event)
        m_event();
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