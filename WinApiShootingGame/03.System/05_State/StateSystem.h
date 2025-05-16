#pragma once

struct State;

class StateSystem : public ComponentSystem, public IDataProvider<State> {
private:
    State* m_state;

public:
    StateSystem(CActor* onwer, State* state);
    virtual ~StateSystem();
    virtual void Init() override;
    void Update(float _deltaTime) override;
    void TakeDamage(int dmg);
    bool IsDead() const;
    State& GetData() const override;
};
