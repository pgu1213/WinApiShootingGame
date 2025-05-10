#pragma once
struct Transform;

class TransformSystem : public ComponentSystem, public IDataProvider<Transform>{
private:     
    Transform* m_transform;   
    int Speed;
public:
    TransformSystem(MainGame* maingame, Entity id, Transform* transform = nullptr);
    virtual ~TransformSystem();
    virtual void Update() override;    
    const Transform& GetData() const override;
};
