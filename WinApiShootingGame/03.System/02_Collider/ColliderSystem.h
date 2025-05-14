#pragma once
#include "../ComponentSystem.h"
struct Collider;

class ColliderSystem : public ComponentSystem, public IDataProvider<Collider> {
private:
    Collider* m_collider;
    function<void(CActor*)> m_onCollision;

public:
    ColliderSystem(CActor* owenr, Collider* collider);
    virtual ~ColliderSystem();
    virtual void Init() override;
    const Collider& GetData() const override;
    virtual void Update(float _deltaTime) override;

    void SetOnCollisionEvent(function<void(CActor*)> func);
    void InvokeCollisionEvent(CActor* other)const;
    // 寇何 面倒 贸府 夸没
};