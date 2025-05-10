#pragma once
struct Transform;
struct Rigidbody;

class TransformSystem : public ComponentSystem, public IDataProvider<Transform>{
private:     
    Transform* m_transform;  
    const Rigidbody& m_rigidbody;
    int Speed;
public:
    TransformSystem(MainGame* maingame, Entity id, Transform* transform = nullptr);
    virtual ~TransformSystem();
    virtual void Update() override;    
    const Transform& GetData() const override;
};
