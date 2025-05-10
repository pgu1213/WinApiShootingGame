#pragma once
struct Rigidbody;

class RigidbodySystem : public ComponentSystem , public IDataProvider<Rigidbody>{
private:
    Rigidbody* m_rigidbody;
public:
    RigidbodySystem(CObject* owner, Rigidbody* rigid = nullptr);
    virtual ~RigidbodySystem();
    const Rigidbody& GetData() const override;
    void Update(float _deltaTime) override;
};
