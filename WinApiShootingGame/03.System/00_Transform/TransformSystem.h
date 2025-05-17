#pragma once
struct Transform;
struct Rigidbody;

class TransformSystem : public ComponentSystem, public IDataProvider<Transform>{
private:     
    Transform* m_transform;  
    const Rigidbody* rigid;
public:
    TransformSystem(CActor* owner, Transform* transform = nullptr);
    virtual ~TransformSystem();
    virtual void Init() override;
    virtual void Update(float _deltaTime) override;
    Transform& GetData() const override;
   void operator=(Transform& trans);
};
