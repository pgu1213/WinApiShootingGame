#pragma once
struct Rigidbody;

class RigidbodySystem : public ComponentSystem , public IDataProvider<Rigidbody>{
private:
    Rigidbody* m_rigidbody;
public:
    RigidbodySystem(CActor* owner, Rigidbody* rigid = nullptr);
    virtual ~RigidbodySystem();
    virtual void Init() override;
    void Update(float _deltaTime) override;
    const Rigidbody& GetData() const override;
};
