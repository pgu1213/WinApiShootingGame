#include "../../pch.h"
#include "GameManager.h"
#include "../03.TimeManager/TimeManager.h"
#include "../05.CollisionManager/CollisionManager.h"

#include "../../01.Object/00.Default/CObject.h"
#include "../../01.Object/01.Actor/CActor.h"
#include "../../01.Object/02.Player/CPlayer.h"
#include "../../01.Object/03_Bullet/CBullet.h"
#include "../../01.Object/04_Enemy/CEnemy.h"


GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	delete collisionManager;
	for (auto& entity : m_entityTable)
	{
		delete entity.second;
	}
}

// 씬 관련 설정
bool GameManager::Init()
{
	/*
	CurrentScene = new Scene(); 씬 객체 생성
	if (!CurrentScene)
	{
		return false;
	}
	CurrentScene->Init();
	*/

	// Object::Init();
	currentEntityID = 0;
	hdc = GetDC(g_hWnd);

	collisionManager = new CollisionManager(this);

	GeneratePlayer();
	GenerateEnemy();

	return true;
}

// 씬을 Update 하기 위함
void GameManager::Update(float DeltaTime)
{
	if (DeltaTime < 0.0f)
	{
		return; // 델타 시간이 유효하지 않으면 업데이트 하지 않음
	}

	for (auto& objs : m_entityTable)
	{
		objs.second->Update(DeltaTime);
	}

	collisionManager->ProcessCollisions();

	if (!removeEntityVec.empty())
	{
		for (Entity id : removeEntityVec) {
			RemoveEntity(id);
		}
		removeEntityVec.clear();
	}
}

void GameManager::Render(HDC hdc)
{
	Vector2 screenSize = GetScreenSize();
	Rectangle(hdc, 0, 0, screenSize.x, screenSize.y);

	for (auto& objs : m_entityTable)
	{
		objs.second->Render(hdc);
	}
}

Entity GameManager::CreateEntity()
{
	return ++currentEntityID == NULL ? 0 : currentEntityID;
}

void GameManager::GeneratePlayer()
{
	playerId = CreateEntity();
	CActor* obj = new CPlayer();
	AddEntityTable(playerId, obj);

	obj->Init(playerId, EntityType::Player);
}

void GameManager::GenerateEnemy()
{
	Entity enemyId = CreateEntity();
	CActor* obj = new CEnemy;
	AddEntityTable(enemyId, obj);
	
	static_cast<CEnemy*>(obj)->SetTarget(playerId);
	obj->Init(enemyId, EntityType::Enemy);
}

Vector2 GameManager::GetScreenSize()
{
	RECT winRect;
	float width = 0;
	float height = 0;
	if (g_hWnd != NULL)
	{
		GetClientRect(g_hWnd, &winRect);

		width = static_cast<float>(winRect.right - winRect.left);
		height = static_cast<float>(winRect.bottom - winRect.top);
	}
	return Vector2{ width, height };
}

void GameManager::RemoveEntity(Entity id)
{
	auto objIter = m_entityTable.find(id);
	if (objIter != m_entityTable.end()) {
		delete objIter->second;
		m_entityTable.erase(objIter);  		
	}
}

Vector2 GameManager::Normalize(Vector2 v)
{
	return Vector2();
}

CActor* GameManager::SpawnBullet(Entity shooterId)
{
	Entity bulletId = CreateEntity();
	CActor* shooterObj = m_entityTable[shooterId];
	CActor* obj = new CBullet(*shooterObj);
	AddEntityTable(bulletId, obj);


	EntityType bulletType = EntityType::None;
	if (shooterObj->GetType() == EntityType::Player)
		bulletType = EntityType::PlayerBullet;
	else
		bulletType = EntityType::EnemyBullet;

	obj->Init(bulletId, bulletType);
	
	return obj;

}

CActor* GameManager::SpawnBullet(Entity shooterId, Vector2 pos, Vector2 velocity, Entity targetId)
{
	CActor* obj = SpawnBullet(shooterId);

	static_cast<CBullet*>(obj)->SetBulletDestination(pos, velocity, targetId);

	return obj;
}

const EntityTable* GameManager::GetEntityTable()
{	
	return &m_entityTable;
}

void GameManager::AddRemoveVector(Entity id)
{
	removeEntityVec.emplace_back(id);
}

void GameManager::AddEntityTable(Entity id, CActor* obj)
{
	m_entityTable[id] = obj;
}
