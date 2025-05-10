#pragma once
struct Rigidbody;

class RigidbodySystem : public ComponentSystem , public IDataProvider<Rigidbody>{
private:
    Rigidbody* m_rigidbody;
public:
    RigidbodySystem(MainGame* maingame, Entity id, Rigidbody* rigid = nullptr);
    virtual ~RigidbodySystem();
    const Rigidbody& GetData() const override;
    void Update() override;
};
