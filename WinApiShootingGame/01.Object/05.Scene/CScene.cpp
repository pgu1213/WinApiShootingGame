
#include "../../pch.h"
#include "CScene.h"
#include "../../00.Manager/01.GameManager/GameManager.h"

#include "../../01.Object/00.Default/CObject.h"
#include "../../01.Object/01.Actor/CActor.h"
#include "../../01.Object/02.Player/CPlayer.h"
#include "../../01.Object/03_Bullet/CBullet.h"
#include "../../01.Object/04_Enemy/CEnemy.h"
#include "../../01.Object/05_Boss/CBoss1.h"

CScene::CScene(const std::string& name) : m_SceneName(name)
{
}

CScene::~CScene()
{
    Release();
}

void CScene::Init(Entity id, EntityType type)
{
}

void CScene::Update(float DeltaTime)
{
    for (auto& obj : m_SceneObjectList)
    {
        // obj가 있고 valid면 렌더링
        if (obj.second)
        {
            obj.second->Update(DeltaTime);
        }
    }

    if (!removeEntityVec.empty())
    {
        for (Entity id : removeEntityVec) {
            RemoveEntity(id);
        }
        removeEntityVec.clear();
    }
}

void CScene::Render(HDC hdc)
{
    for (auto& obj : m_SceneObjectList)
    {
        // obj가 있고 valid면 렌더링
        if (obj.second)
        {
            obj.second->Render(hdc);
        }
    }
}

void CScene::Release()
{
    for (auto& obj : m_SceneObjectList)
    {
        if (obj.second) // 유효성 체크
        {
            delete obj.second; // 메모리 해제
        }
    }
    m_SceneObjectList.clear(); // 리스트 비우기
}

void CScene::GeneratePlayer()
{
    playerId = GameManager::GetInstance()->CreateEntity();
    CActor* obj = new CPlayer();
    AddEntityTable(playerId, obj);

    obj->Init(playerId, EntityType::Player);
}

void CScene::GenerateEnemy()
{
    Entity enemyId = GameManager::GetInstance()->CreateEntity();
    CActor* obj = new CEnemy;
    AddEntityTable(enemyId, obj);

    static_cast<CEnemy*>(obj)->SetTarget(playerId);
    obj->Init(enemyId, EntityType::Enemy);
}

CActor* CScene::SpawnBullet(Entity shooterId, float _damage, float _speed, Vector2 bulletDirection)
{
    Entity bulletId = GameManager::GetInstance()->CreateEntity();
    CActor* shooterObj = m_SceneObjectList[shooterId];
    CActor* obj = new CBullet(*shooterObj, _damage, _speed);
    AddEntityTable(bulletId, obj);


    EntityType bulletType = EntityType::None;
    if (shooterObj->GetType() == EntityType::Player)
        bulletType = EntityType::PlayerBullet;
    else
        bulletType = EntityType::EnemyBullet;

    obj->Init(bulletId, bulletType);

    static_cast<CBullet*>(obj)->SetBulletDirection(bulletDirection);

    return obj;
}

const string& CScene::GetSceneName() const
{
    return m_SceneName;
}

const unordered_map<Entity, CActor*>* CScene::GetSceneObjectList() const
{
    return &m_SceneObjectList;
}

void CScene::AddRemoveVector(Entity id)
{
    removeEntityVec.emplace_back(id);
}

void CScene::AddEntityTable(Entity id, CActor* obj)
{
    m_SceneObjectList[id] = obj;
}

void CScene::RemoveEntity(Entity id)
{
    auto objIter = m_SceneObjectList.find(id);
    if (objIter != m_SceneObjectList.end()) {
        delete objIter->second;
        m_SceneObjectList.erase(objIter);
    }
}
