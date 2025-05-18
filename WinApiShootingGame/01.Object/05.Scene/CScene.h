#pragma once
#include "../00.Default/CObject.h"

class CActor;

class CScene : public CObject
{
public:
    CScene(const std::string& name);
    virtual ~CScene() override;
public:
    virtual void Init(Entity id, EntityType type) override;
    virtual void Update(float DeltaTime) override;
    virtual void Release() override;
    virtual void Render(HDC hdc);
protected:
    void GeneratePlayer();
    void GenerateEnemy();

    void AddEntityTable(Entity id, CActor* obj);
    void RemoveEntity(Entity id);
public:
    CActor* SpawnBullet(Entity shooterId, float _damage, float _speed, Vector2 bulletDirection);

    void AddRemoveVector(Entity id);
    const string& GetSceneName() const;
	const unordered_map<Entity, CActor*>* GetSceneObjectList() const;
private:
    string m_SceneName;

    vector<Entity> removeEntityVec;
    unordered_map<Entity, CActor*> m_SceneObjectList;

    Entity playerId;
    Entity currentEntityID;
};