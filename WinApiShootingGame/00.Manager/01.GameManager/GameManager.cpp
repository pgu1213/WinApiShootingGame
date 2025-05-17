#include "../../pch.h"
#include "GameManager.h"
#include "../03.TimeManager/TimeManager.h"
#include "../05.CollisionManager/CollisionManager.h"

#include "../../01.Object/00.Default/CObject.h"
#include "../../01.Object/01.Actor/CActor.h"
#include "../../01.Object/02.Player/CPlayer.h"
#include "../../01.Object/03_Bullet/CBullet.h"
#include "../../01.Object/04_Enemy/CEnemy.h"
#include "../../01.Object/05_Boss/CBoss1.h"

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
	srand(static_cast<unsigned int>(time(NULL)));
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

	GenerateBoss1();
	
	//GenerateEnemy();
	//GenerateEnemy();
	//GenerateEnemy();
	//GenerateEnemy();

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


	HDC memDC = CreateCompatibleDC(hdc);
	if (!memDC) return;

	HBITMAP memBitmap = CreateCompatibleBitmap(hdc, (int)screenSize.x, (int)screenSize.y);
	HGDIOBJ oldBitmap = SelectObject(memDC, memBitmap);


	HBRUSH hbr = (HBRUSH)(COLOR_WINDOW + 1);
	RECT rect = { 0, 0, (LONG)screenSize.x, (LONG)screenSize.y };
	FillRect(memDC, &rect, hbr);

	for (auto& objs : m_entityTable)
	{
		objs.second->Render(memDC);
	}

	BitBlt(hdc, 0, 0, (int)screenSize.x, (int)screenSize.y, memDC, 0, 0, SRCCOPY);

	SelectObject(memDC, oldBitmap);
	DeleteObject(memBitmap);
	DeleteDC(memDC);
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

void GameManager::GenerateBoss1()
{
	Entity bossId = CreateEntity();
	CActor* obj = new CBoss1();
	AddEntityTable(bossId, obj);

	static_cast<CEnemy*>(obj)->SetTarget(playerId);
	obj->Init(bossId, EntityType::Enemy);
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

CActor* GameManager::SpawnBullet(Entity shooterId, float _damage, float _speed, Vector2 bulletDirection)
{
	Entity bulletId = CreateEntity();
	CActor* shooterObj = m_entityTable[shooterId];
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
