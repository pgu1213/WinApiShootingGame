#pragma once
#include "../ComponentSystem.h"
struct Collider;

class ColliderSystem : public ComponentSystem, public IDataProvider<Collider> {
private:
    Collider* m_collider;
    function<void(CObject*)> m_onCollision;

public:
    ColliderSystem(CObject* owenr, Collider* collider);
    virtual ~ColliderSystem();
    virtual void Init() override;
    const Collider& GetData() const override;
    virtual void Update(float _deltaTime) override;
	virtual void Render(HDC hdc) override;

    void SetOnCollisionEvent(function<void(CObject*)> func);
    void InvokeCollisionEvent(CObject* other)const; 
    // 寇何 面倒 贸府 夸没
};