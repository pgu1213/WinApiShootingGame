#include "../../pch.h"
#include "GameManager.h"
#include "../03.TimeManager/TimeManager.h"
#include "../04.InputManager/InputManager.h"
#include "../05.CollisionManager/CollisionManager.h"

#include "../../01.Object/00.Default/CObject.h"

#include "../../03.System/ComponentSystem.h"
#include "../../03.System/00_Transform/TransformSystem.h"
#include "../../03.System/01_SpriteRenderer/SpriteRendererSystem.h"
#include "../../03.System/02_Collider/ColliderSystem.h"
#include "../../03.System/03_Input/InputSystem.h"
#include "../../03.System/04_Rigid/RigidbodySystem.h"
#include "../../03.System/05_State/StateSystem.h"
#include "../../03.System/06_CoolTime/CoolTimeSystem.h"

#include "../../02.Component/Transform.h"
#include "../../02.Component/Rigidbody.h"
#include "../../02.Component/InputData.h"
#include "../../02.Component/Collider.h"
#include "../../02.Component/State.h"
#include "../../02.Component/CoolTime.h"

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

	hdc = GetDC(g_hWnd);

	inputManager = new InputManager();
	inputManager->BindAxisKey(VK_LEFT, VK_RIGHT, "Horizontal");
	inputManager->BindAxisKey(VK_UP, VK_DOWN, "Vertical");
	inputManager->BindActionKey(VK_SPACE, "Shoot");

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

	Vector2 screenSize = GetScreenSize();
	Rectangle(hdc, 0, 0, screenSize.x, screenSize.y);
	// TODO - 씬 업데이트
	// GetList > 리스트 새로 업데이트만 시키고
}

Entity GameManager::CreateEntity()
{
	return ++currentEntityID;
}

void GameManager::GeneratePlayer()
{
	Entity playerId = CreateEntity();
	ComponentTable m_componentTable;
	AddEntityTable(playerId);

	CObject* obj = m_entityTable[playerId];

	Transform* transform = new Transform{ Vector2{ 300.f,300.f }, 0.f, Vector2{ 50.f,50.f } };
	TransformSystem* transformSystem = new TransformSystem(obj, transform);
	Rigidbody* rigid = new Rigidbody();
	RigidbodySystem* rigidSystem = new RigidbodySystem(obj, rigid);

	m_componentTable[typeid(InputSystem)] = new InputSystem(obj, this, inputManager);
	m_componentTable[typeid(RigidbodySystem)] = rigidSystem;
	m_componentTable[typeid(TransformSystem)] = transformSystem;
	m_componentTable[typeid(SpriteRendererSystem)] = new SpriteRendererSystem(obj, hdc);

	Vector2 screenSize = GetScreenSize();

	transformSystem->AddEvent([=]() {
		transform->position.x = clamp(
			transform->position.x,
			transform->scale.x / 2,
			screenSize.x - transform->scale.x / 2
		);
		transform->position.y = clamp(
			transform->position.y,
			transform->scale.y / 2,
			screenSize.y - transform->scale.y / 2
		);
		});

	rigidSystem->AddEvent([=]() {
		const InputData& input = GetComponent<InputSystem>(playerId)->GetData();

		rigid->velocity.x = input.horizontal;
		rigid->velocity.y = input.vertical;
		});

	obj->Init(playerId, m_componentTable);
	m_gameObjectTable[playerId] = m_componentTable;
}

void GameManager::GenerateEnemy()
{

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
}

Vector2 GameManager::Normalize(Vector2 v)
{
	return Vector2();
}

void GameManager::SpawnBullet(Entity shooterId)
{
	Entity bulletId = CreateEntity();
	ComponentTable bulletTable;
	AddEntityTable(bulletId);

	CObject* obj = m_entityTable[bulletId];

	const Transform& shooterTransform = GetComponent<TransformSystem>(shooterId)->GetData();
	Transform* transform = new Transform{ shooterTransform.position, 0.f, Vector2{30.f, 30.f} };
	Rigidbody* rigid = new Rigidbody{ Vector2{0.f, -3.f} };
	Collider* collider = new Collider{ {0.f, 0.f}, transform->scale };

	TransformSystem* transformSystem = new TransformSystem(obj,  transform);
	RigidbodySystem* rigidSystem = new RigidbodySystem(obj,  rigid);
	SpriteRendererSystem* spriteSystem = new SpriteRendererSystem(obj,  hdc);
	ColliderSystem* colliderSystem = new ColliderSystem(obj,  collider);

	bulletTable[typeid(TransformSystem)] = transformSystem;
	bulletTable[typeid(ColliderSystem)] = colliderSystem;
	bulletTable[typeid(RigidbodySystem)] = rigidSystem;
	bulletTable[typeid(SpriteRendererSystem)] = spriteSystem;

	Vector2 screenSize = GetScreenSize();

	transformSystem->AddEvent([=]() {
		const Transform& transform = transformSystem->GetData();
		if (transform.position.y < 0 || transform.position.y > screenSize.y) {
			this->removeEntityQueue.emplace_back(bulletId);;
		}
		});

	colliderSystem->SetOnCollisionEvent([=](Entity otherId) {
		EntityType type = GetEntityType(otherId);
		EntityType bulletType = GetEntityType(bulletId);
		if ((type == EntityType::Enemy && bulletType == EntityType::PlayerBullet) || (type == EntityType::Player && bulletType == EntityType::EnemyBullet)) {
			removeEntityQueue.emplace_back(bulletId);
		}
		});

	m_gameObjectTable[bulletId] = bulletTable;
}

void GameManager::SpawnBullet(Entity shooterId, Vector2 pos, Vector2 velocity)
{
	Entity bulletId = CreateEntity();
	ComponentTable bulletTable;
	AddEntityTable(bulletId);

	CObject* obj = m_entityTable[bulletId];

	Transform* transform = new Transform{ pos, 0.f, Vector2{20.f, 20.f} };
	Rigidbody* rigid = new Rigidbody{ velocity };
	Collider* collider = new Collider{ {0.f, 0.f}, transform->scale };

	TransformSystem* transformSystem = new TransformSystem(obj, transform);
	RigidbodySystem* rigidSystem = new RigidbodySystem(obj, rigid);
	ColliderSystem* colliderSystem = new ColliderSystem(obj, collider);
	SpriteRendererSystem* spriteSystem = new SpriteRendererSystem(obj, hdc);

	ComponentTable table;
	table[typeid(TransformSystem)] = transformSystem;
	table[typeid(RigidbodySystem)] = rigidSystem;
	table[typeid(ColliderSystem)] = colliderSystem;
	table[typeid(SpriteRendererSystem)] = spriteSystem;

	Vector2 screenSize = GetScreenSize();

	transformSystem->AddEvent([=]() {
		const Transform& transform = transformSystem->GetData();
		if (transform.position.y < 0 || transform.position.y > screenSize.y) {
			this->removeEntityQueue.emplace_back(bulletId);;
		}
		});

	colliderSystem->SetOnCollisionEvent([=](Entity otherId) {
		EntityType type = GetEntityType(otherId);
		EntityType bulletType = GetEntityType(bulletId);
		if ((type == EntityType::Enemy && bulletType == EntityType::PlayerBullet) || (type == EntityType::Player && bulletType == EntityType::EnemyBullet)) {
			removeEntityQueue.emplace_back(bulletId);
		}
		});

	m_gameObjectTable[bulletId] = table;
}

const ObjectTable* GameManager::GetObjectTable()const
{
	return &m_gameObjectTable;
}

const EntityTable* GameManager::GetEntityTable()const
{
	return &m_entityTable;
}

EntityType GameManager::GetEntityType(Entity id) const
{
	return EntityType();
}

void GameManager::AddEntityTable(Entity id)
{
	m_entityTable[id] = new CObject("Obj"+id);
}
