#pragma once
struct Transform;
struct Rigidbody;

class TransformSystem : public ComponentSystem, public IDataProvider<Transform>{
private:     
    Transform* m_transform;  
public:
    TransformSystem(CActor* owner, Transform* transform = nullptr);
    virtual ~TransformSystem();
    virtual void Init() override;
    virtual void Update(float _deltaTime) override;
    const Transform& GetData() const override;
};
