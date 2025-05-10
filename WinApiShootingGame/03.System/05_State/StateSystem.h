#pragma once

struct State;

class StateSystem : public ComponentSystem, public IDataProvider<State> {
private:
    State* m_state;

public:
    StateSystem(MainGame* game, Entity id, State* state);
    virtual ~StateSystem();

    void Update() override;
    void TakeDamage(int dmg);
    bool IsDead() const;
    const State& GetData() const override;
};
