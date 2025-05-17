#include "../../pch.h"
#include "CEnemy.h"
#include "../../00.Manager/01.GameManager/GameManager.h"
#include "../../03.System/ComponentSystem.h"

#include "../../03.System/00_Transform/TransformSystem.h"
#include "../../03.System/01_SpriteRenderer/SpriteRendererSystem.h"
#include "../../03.System/03_Rigid/RigidbodySystem.h"
#include "../../03.System/02_Collider/ColliderSystem.h"
#include "../../03.System/04_CoolTime/CoolTimeSystem.h"

#include "../../02.Component/Transform.h"
#include "../../02.Component/SpriteRenderer.h"
#include "../../02.Component/Collider.h"
#include "../../02.Component/Rigidbody.h"
#include "../../02.Component/CoolTime.h"

#include "../03_Bullet/CBullet.h"
#include "../../01.Object/IEnemyMove.h"
#include "../../01.Object/99_EnemyMove/RandomMove/EnemyMove_RandomMove.h"
#include "../../01.Object/99_EnemyMove/FixedPath/EnemyMove_FixedPathMove.h"
#include "../../01.Object/99_EnemyMove/Static/EnemyMove_StaticMove.h"


CEnemy::CEnemy() : target(nullptr), currentHP(5), maxHP(5), speed(100.f), damage(1), isMoveAble(true)
{

}

CEnemy::~CEnemy()
{
}

void CEnemy::Init(Entity id, EntityType type)
{
	Vector2 point = SpawnOutScreen();
	Vector2 screenSize = GameManager::GetInstance()->GetScreenSize();

	// 진입 목표 위치 계산
	if (point.y < 0)  // 위
	{
		float targetX = clamp(static_cast<float>(point.x), 0.f, screenSize.x);
		float targetY = 100.f + static_cast<float>(rand() % 101);
		enterTargetPos = Vector2{ targetX, clamp(targetY, 0.f, screenSize.y) };
	}
	else if (point.x < 0)  // 왼쪽
	{
		float targetX = 100.f + static_cast<float>(rand() % 101);
		float targetY = clamp(static_cast<float>(point.y), 0.f, screenSize.y);
		enterTargetPos = Vector2{ clamp(targetX, 0.f, screenSize.x), targetY };
	}
	else if (point.x > screenSize.x)  // 오른쪽
	{
		float targetX = screenSize.x - (100.f + static_cast<float>(rand() % 101));
		float targetY = clamp(static_cast<float>(point.y), 0.f, screenSize.y);
		enterTargetPos = Vector2{ clamp(targetX, 0.f, screenSize.x), targetY };
	}
	else
	{
		enterTargetPos = Vector2{ screenSize.x * 0.5f, screenSize.y * 0.5f };
	}
	
	moveDestination = enterTargetPos;
	isEnteringScreen = true;

	switch (rand() % 2)
	{
	case 0:
		moveLogic = new EnemyMove_RandomMove();
		break;
	case 1:
		moveLogic = new EnemyMove_FixedPathMove();
		break;
	case 2:
	default:
		moveLogic = new EnemyMove_StaticMove();
		break;
	}

	Transform* transform = new Transform{ Vector2{ (float)point.x, (float)point.y }, 0.f, Vector2{ 50.f,50.f } };
	TransformSystem* transformSystem = new TransformSystem(this, transform);

	Rigidbody* rigid = new Rigidbody{ speed, speed };
	RigidbodySystem* rigidSystem = new RigidbodySystem(this, rigid);

	Collider* collider = new Collider{ {0.f, 0.f}, transform->scale };
	ColliderSystem* colliderSystem = new ColliderSystem(this, collider);

	SpriteRendererSystem* spriteSystem = new SpriteRendererSystem(this, GetDC(g_hWnd));

	CoolTimeSystem* coolTimeSystem = new CoolTimeSystem(this);

	m_componentTable[typeid(CoolTimeSystem)] = coolTimeSystem;
	m_componentTable[typeid(RigidbodySystem)] = rigidSystem;
	m_componentTable[typeid(ColliderSystem)] = colliderSystem;
	m_componentTable[typeid(TransformSystem)] = transformSystem;
	m_componentTable[typeid(SpriteRendererSystem)] = spriteSystem;

	CActor::Init(id, type);

	render = dynamic_cast<IRenderer*>(m_componentTable[typeid(SpriteRendererSystem)]);

	SpriteRenderer& playerSpriteData = spriteSystem->GetModifyData();
	playerSpriteData.filePath = L"05.Resource/01.Sprite/EnemyTest.png";

	transformSystem->AddEvent([=]() {
		if (!isEnteringScreen)
		{
			transform->position.x = clamp(
				transform->position.x,
				transform->scale.x / 2,
				GameManager::GetScreenSize().x - transform->scale.x / 2
			);
			transform->position.y = clamp(
				transform->position.y,
				transform->scale.y / 2,
				GameManager::GetScreenSize().y - transform->scale.y / 2
			);
		}
		});

	rigidSystem->AddEvent([=]() {
		Vector2 currentPos = transform->position;
		Vector2 currentScale = transform->scale;		

		float distToTarget = GetDistance(currentPos, moveDestination);
		if (distToTarget < 5.f)
		{
			if (isEnteringScreen) isEnteringScreen = false;
			if (moveLogic)
				moveDestination = moveLogic->GetNextPosition(currentPos, currentScale);
		}

		rigid->velocity = GetMoveTward(currentPos, moveDestination);
	});

	// 충돌 이벤트 등록: 총알에 맞으면 HP 감소
	colliderSystem->SetOnCollisionEvent([=](CActor* obj) {
		if (obj->GetType() == EntityType::PlayerBullet) {
			currentHP -= static_cast<CBullet*>(obj)->GetDamage();
			if (currentHP <= 0) {
				m_bIsValid = false;
				GameManager::GetInstance()->AddRemoveVector(id);
			}
			GameManager::GetInstance()->AddRemoveVector(obj->GetId());
		}
		});

	coolTimeSystem->AddTimer("shoot", 3.f, [=]() {
		if (target != nullptr)
			GameManager::GetInstance()->SpawnBullet(id, damage, target->GetId());
		coolTimeSystem->StartCooldown("shoot");
		});

	coolTimeSystem->AddTimer("move", 3.f, [=]() {
		isMoveAble = true;
		coolTimeSystem->StartCooldown("move");
		});

	coolTimeSystem->StartCooldown("shoot");
	coolTimeSystem->StartCooldown("move");
}

void CEnemy::Update(float DeltaTime)
{
	CActor::Update(DeltaTime);
}

void CEnemy::Render(HDC hdc)
{
	render->Render(hdc);
}

Vector2 CEnemy::SpawnOutScreen()
{
	Vector2 screenSize = GameManager::GetInstance()->GetScreenSize();
	Vector2 vec;

	int side = rand() % 3; // 0: 위, 1: 왼쪽, 2: 오른쪽

	switch (side)
	{
	case 0: // 위쪽
		vec.x = rand() % static_cast<int>(screenSize.x);
		vec.y = -50;
		break;
	case 1: // 왼쪽
		vec.x = -50;
		vec.y = rand() % static_cast<int>(screenSize.y / 2.f);
		break;
	case 2: // 오른쪽
		vec.x = static_cast<int>(screenSize.x) + 50;
		vec.y = rand() % static_cast<int>(screenSize.y / 2.f);
		break;
	default:
		vec.x = 0;
		vec.y = 0;
		break;
	}
	return vec;
}


Vector2 CEnemy::GetMoveTward(Vector2 current, Vector2 target)
{
	Vector2 dir = { target.x - current.x, target.y - current.y };
	float dist = GetDistance(current, target);

	if (dist == 0.f)
		return Vector2{ 0.f, 0.f };

	Vector2 normDir = Normalize(dir);

	return { normDir.x * speed, normDir.y * speed };
}

void CEnemy::Release()
{
	delete moveLogic;
	moveLogic = nullptr;
}

CActor* CEnemy::GetTarget()
{
	return target;
}

void CEnemy::SetTarget(Entity id)
{
	target = GameManager::GetInstance()
		->GetEntityTable()->find(id)->second;
}

