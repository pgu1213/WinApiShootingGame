#pragma once

struct State;

class StateSystem : public ComponentSystem, public IDataProvider<State> {
private:
    State* m_state;

public:
    StateSystem(CObject* onwer, State* state);
    virtual ~StateSystem();

    void Update(float _deltaTime) override;
    void TakeDamage(int dmg);
    bool IsDead() const;
    const State& GetData() const override;
};
