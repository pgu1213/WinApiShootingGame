#include "../../pch.h"
#include "GameManager.h"
#include "../03.TimeManager/TimeManager.h"
#include "../04.InputManager/InputManager.h"
#include "../05.CollisionManager/CollisionManager.h"

#include "../../01.Object/00.Default/CObject.h"
#include "../../01.Object/01.Actor/CActor.h"
#include "../../01.Object/02.Player/CPlayer.h"


GameManager::GameManager()
{
}

GameManager::~GameManager()
{
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

	if (!removeEntityQueue.empty())
	{
       		for (Entity id : removeEntityQueue) {
			RemoveEntity(id);
		}
		removeEntityQueue.clear();
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

//void GameManager::GenerateEnemy()
//{
//	Entity enemyId = CreateEntity();
//
//	CObject* obj = new CActor;
//	AddEntityTable(enemyId, obj);
//	ComponentTable m_componentTable;
//
//	Transform* transform = new Transform{ Vector2{ 100.f,100.f }, 0.f, Vector2{ 50.f,50.f } };
//	TransformSystem* transformSystem = new TransformSystem(obj, transform);
//
//	Rigidbody* rigid = new Rigidbody();
//	RigidbodySystem* rigidSystem = new RigidbodySystem(obj, rigid);
//
//	Collider* collider = new Collider{ {0.f, 0.f}, transform->scale };
//	ColliderSystem* colliderSystem = new ColliderSystem(obj, collider);
//
//	State* state = new State{ 3, 3, 0 };
//	StateSystem* stateSystem = new StateSystem(obj, state);
//
//	CoolTime* coolTime = new CoolTime{ 0.f , 3.f };
//	CoolTimeSystem* coolTimeSystem = new CoolTimeSystem(obj, coolTime);
//
//	m_componentTable[typeid(CoolTimeSystem)] = coolTimeSystem;
//	m_componentTable[typeid(RigidbodySystem)] = rigidSystem;
//	m_componentTable[typeid(ColliderSystem)] = colliderSystem;
//	m_componentTable[typeid(TransformSystem)] = transformSystem;
//	m_componentTable[typeid(SpriteRendererSystem)] = new SpriteRendererSystem(obj, hdc);
//	m_componentTable[typeid(StateSystem)] = stateSystem;
//
//	// 충돌 이벤트 등록: 총알에 맞으면 HP 감소
//	colliderSystem->SetOnCollisionEvent([=](CObject* obj) {
//		if (obj->GetType() == EntityType::PlayerBullet) {
//			stateSystem->TakeDamage(1);
//			if (stateSystem->IsDead()) {
//				this->removeEntityQueue.emplace_back(enemyId);
//			}
//			this->removeEntityQueue.emplace_back(obj->GetId());
//		}
//		});
//
//	coolTimeSystem->AddEvent([=]() {
//		Vector2 enemyPos = transform->position;
//		Vector2 playerPos = m_entityTable[enemyId]->GetComponent<TransformSystem>()->GetData().position;
//		Vector2 vec = { playerPos.x - enemyPos.x , playerPos.y - enemyPos.y };
//		Vector2 dir = Normalize(vec);
//		Vector2 vel = Vector2{ dir.x * 80.f, dir.y * 80.f };
//
//		SpawnBullet(enemyId, enemyPos, vel);
//		// Bullet 생성 함수 호출
//		coolTimeSystem->StartCooldown(); // 쿨타임 재시작
//		});
//
//	coolTimeSystem->StartCooldown();
//
//	obj->Init(enemyId, EntityType::Enemy);
//}

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
	auto objIter= m_entityTable.find(id);
	if (objIter != m_entityTable.end()) {
		m_entityTable.erase(objIter);
	}
}

Vector2 GameManager::Normalize(Vector2 v)
{
	return Vector2();
}

//void GameManager::SpawnBullet(Entity shooterId)
//{
//	Entity bulletId = CreateEntity();
//	CObject* obj = new CActor();
//	AddEntityTable(bulletId, obj);
//	CObject* shooterObj = m_entityTable[shooterId];
//
//	EntityType bulletType = EntityType::None;
//	if (shooterObj->GetType() == EntityType::Player)
//		bulletType = EntityType::PlayerBullet;
//	else
//		bulletType = EntityType::EnemyBullet;
//
//	ComponentTable bulletTable;
//
//	const Transform& shooterTransform = m_entityTable[shooterId]->GetComponent<TransformSystem>()->GetData();
//
//	Transform* transform = new Transform{ shooterTransform.position, 0.f, Vector2{30.f, 30.f} };
//	Rigidbody* rigid = new Rigidbody{ Vector2{0.f, -100.f} };
//	Collider* collider = new Collider{ {0.f, 0.f}, transform->scale };
//
//	TransformSystem* transformSystem = new TransformSystem(obj,  transform);
//	RigidbodySystem* rigidSystem = new RigidbodySystem(obj, rigid);
//	SpriteRendererSystem* spriteSystem = new SpriteRendererSystem(obj,  hdc);
//	ColliderSystem* colliderSystem = new ColliderSystem(obj,  collider);
//
//	bulletTable[typeid(TransformSystem)] = transformSystem;
//	bulletTable[typeid(ColliderSystem)] = colliderSystem;
//	bulletTable[typeid(RigidbodySystem)] = rigidSystem;
//	bulletTable[typeid(SpriteRendererSystem)] = spriteSystem;
//
//	Vector2 screenSize = GetScreenSize();
//
//	transformSystem->AddEvent([=]() {
//		const Transform& transform = transformSystem->GetData();
//		if (transform.position.y < 0 || transform.position.y > screenSize.y) {
//			removeEntityQueue.emplace_back(bulletId);
//		}
//		});
//
//	colliderSystem->SetOnCollisionEvent([=](CObject* obj) {
//		EntityType type = obj->GetType();
//		EntityType bulletType = obj->GetType();
//		if ((type == EntityType::Enemy && bulletType == EntityType::PlayerBullet) || (type == EntityType::Player && bulletType == EntityType::EnemyBullet)) {
//			removeEntityQueue.emplace_back(bulletId);
//		}
//		});
//
//
//	obj->Init(bulletId, bulletType);
//}

//void GameManager::SpawnBullet(Entity shooterId, Vector2 pos, Vector2 velocity)
//{
//	Entity bulletId = CreateEntity();
//	CActor* obj = new CActor();
//	AddEntityTable(bulletId, obj);
//	CActor* shooterObj = m_entityTable[shooterId];
//	
//	EntityType bulletType = EntityType::None;
//	if (shooterObj->GetType() == EntityType::Player)
//		bulletType = EntityType::PlayerBullet;
//	else
//		bulletType = EntityType::EnemyBullet;
//
//	ComponentTable bulletTable;
//
//	Transform* transform = new Transform{ pos, 0.f, Vector2{20.f, 20.f} };
//	Rigidbody* rigid = new Rigidbody{ velocity };
//	Collider* collider = new Collider{ {0.f, 0.f}, transform->scale };
//
//	TransformSystem* transformSystem = new TransformSystem(obj, transform);
//	RigidbodySystem* rigidSystem = new RigidbodySystem(obj, rigid);
//	ColliderSystem* colliderSystem = new ColliderSystem(obj, collider);
//	SpriteRendererSystem* spriteSystem = new SpriteRendererSystem(obj, hdc);
//
//	bulletTable[typeid(TransformSystem)] = transformSystem;
//	bulletTable[typeid(RigidbodySystem)] = rigidSystem;
//	bulletTable[typeid(ColliderSystem)] = colliderSystem;
//	bulletTable[typeid(SpriteRendererSystem)] = spriteSystem;
//
//	Vector2 screenSize = GetScreenSize();
//
//	transformSystem->AddEvent([=]() {
//		const Transform& transform = transformSystem->GetData();
//		if (transform.position.y < 0 || transform.position.y > screenSize.y) {
//			this->removeEntityQueue.emplace_back(bulletId);;
//		}
//		});
//
//	colliderSystem->SetOnCollisionEvent([=](CObject* obj) {
//		EntityType type = obj->GetType();
//		EntityType bulletType = obj->GetType();
//		if ((type == EntityType::Enemy && bulletType == EntityType::PlayerBullet) || (type == EntityType::Player && bulletType == EntityType::EnemyBullet)) {
//			removeEntityQueue.emplace_back(bulletId);
//		}
//		});
//
//	obj->Init(bulletId, shooterObj->GetType());
//}

const EntityTable* GameManager::GetEntityTable() const
{
	return &m_entityTable;
}

void GameManager::AddEntityTable(Entity id, CActor* obj)
{
	m_entityTable[id] = obj;
}
