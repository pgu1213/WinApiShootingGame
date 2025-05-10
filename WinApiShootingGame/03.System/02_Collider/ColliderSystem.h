#pragma once
#include "../ComponentSystem.h"
struct Collider;

class ColliderSystem : public ComponentSystem, public IDataProvider<Collider> {
private:
    Collider* m_collider;
    function<void(Entity)> m_onCollision;

public:
    ColliderSystem(CObject* owenr, Collider* collider);
    virtual ~ColliderSystem();
    const Collider& GetData() const override;
    virtual void Update(float _deltaTime) override;

    void SetOnCollisionEvent(function<void(Entity)> func);
    void InvokeCollisionEvent(Entity other)const; 
    // 寇何 面倒 贸府 夸没
};