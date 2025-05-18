#include "../../pch.h"
#include "CEnemy.h"
#include "../../00.Manager/01.GameManager/GameManager.h"
#include "../../00.Manager/02.SceneManager/SceneManager.h"
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

#include "../05.Scene/CScene.h"
#include "../03_Bullet/CBullet.h"
#include "../IBulletType.h"
#include "../98_BulletType/00.SingleBullet/SingleBullet.h"

#include "../../01.Object/IEnemyMove.h"
#include "../../01.Object/99_EnemyMove/RandomMove/EnemyMove_RandomMove.h"
#include "../../01.Object/99_EnemyMove/FixedPath/EnemyMove_FixedPathMove.h"
#include "../../01.Object/99_EnemyMove/Static/EnemyMove_StaticMove.h"


CEnemy::CEnemy() : target(nullptr), moveLogic(nullptr), currentHP(5), maxHP(5), m_bulletSpeed(200.f), damage(1), speed(200.f),isMoveAble(true), isEnteringScreen(false)
{

}

CEnemy::~CEnemy()
{
	Release();
}

void CEnemy::Init(Entity id, EntityType type)
{
	moveLogic = new EnemyMove_RandomMove(200.f);
	
	//switch (rand() % 3)
	//{
	//case 0:
	//	moveLogic = new EnemyMove_RandomMove(100.f);
	//	break;
	//case 1:
	//	moveLogic = new EnemyMove_FixedPathMove();
	//	break;
	//case 2:
	//default:
	//	moveLogic = new EnemyMove_StaticMove();
	//	break;
	//}

	bulletType.resize((int)BulletType::None);

	bulletType[(int)BulletType::Single] = new SingleBullet();

	Transform* transform = new Transform{ Vector2{ 0.f,0.f }, 0.f, Vector2{ 50.f,50.f } };
	TransformSystem* transformSystem = new TransformSystem(this, transform);

	Rigidbody* rigid = new Rigidbody{ Vector2{speed ,speed } };
	RigidbodySystem* rigidSystem = new RigidbodySystem(this, rigid);

	Collider* collider = new Collider{ ColliderType::Circle, {0.f, 0.f}, {0.f,0.f}, transform->scale.x / 2.f, transform->scale.y / 2.f};
	ColliderSystem* colliderSystem = new ColliderSystem(this, collider);

	SpriteRendererSystem* spriteSystem = new SpriteRendererSystem(this, GetDC(g_hWnd));

	CoolTimeSystem* coolTimeSystem = new CoolTimeSystem(this);

	m_componentTable[typeid(CoolTimeSystem)] = coolTimeSystem;
	m_componentTable[typeid(RigidbodySystem)] = rigidSystem;
	m_componentTable[typeid(ColliderSystem)] = colliderSystem;
	m_componentTable[typeid(TransformSystem)] = transformSystem;
	m_componentTable[typeid(SpriteRendererSystem)] = spriteSystem;

	CActor::Init(id, type);

	Vector2 screenSize = GameManager::GetInstance()->GetScreenSize();

	Vector2 spawnPoint = SpawnOutScreen(transform->scale);

	transform->position = spawnPoint;

	if (spawnPoint.y < 0)  // 위에서 스폰
	{
		float targetX = spawnPoint.x;
		float targetY = 100.f + static_cast<float>(rand() % 101);
		moveDestination = Vector2{ targetX, targetY };
	}
	else if (spawnPoint.x < 0)  // 왼쪽에서 스폰
	{
		float targetX = 100.f + static_cast<float>(rand() % 101);
		float targetY = spawnPoint.y;
		moveDestination = Vector2{ targetX, targetY };
	}
	else if (spawnPoint.x > screenSize.x)  // 오른쪽에서 스폰
	{
		float targetX = screenSize.x - (100.f + static_cast<float>(rand() % 101));
		float targetY = spawnPoint.y;
		moveDestination = Vector2{ targetX, targetY };
	}
	else
	{
		moveDestination = Vector2{ screenSize.x * 0.5f, screenSize.y * 0.5f };
	}

	isEnteringScreen = true;

	render = dynamic_cast<IRenderer*>(m_componentTable[typeid(SpriteRendererSystem)]);

	SpriteRenderer& playerSpriteData = spriteSystem->GetModifyData();
	playerSpriteData.filePath = L"05.Resource/01.Sprite/EnemyTest.png";

	rigidSystem->AddEvent([=]() {
		Vector2 currentPos = transform->position;
		Vector2 currentScale = transform->scale;

		float distToTarget = GetDistance(currentPos, moveDestination);
		if (distToTarget < 5.f && isMoveAble)
		{
			if (isEnteringScreen) isEnteringScreen = false;
			if (moveLogic)
				moveDestination = moveLogic->GetNextPosition(currentPos, currentScale);
			isMoveAble = false;
		}
		
		if (!isMoveAble && distToTarget > 0.f)
		{
			rigid->velocity = Vector2{ 0.0f, 0.0f };
		}
		else
			rigid->velocity = GetMoveTward(currentPos, moveDestination);
	});

	// 충돌 이벤트 등록: 총알에 맞으면 HP 감소
	colliderSystem->SetOnCollisionEvent([=](CActor* obj) {
		if (obj->GetType() == EntityType::PlayerBullet) {
			currentHP -= static_cast<CBullet*>(obj)->GetDamage();
			if (currentHP <= 0) {
				m_bIsValid = false;
				SceneManager::GetInstance()->GetCurrentScene()->AddRemoveVector(id);
			}
			SceneManager::GetInstance()->GetCurrentScene()->AddRemoveVector(obj->GetId());
		}
		});

	coolTimeSystem->AddTimer("shoot", 3.f, [=]() {
		if (target != nullptr && bulletType.size()!=0) {
			Vector2 shooterPos = transform->position;
			Vector2 targetPos = target->GetComponent<TransformSystem>()->GetData().position;
			Vector2 vec = { targetPos.x - shooterPos.x , targetPos.y - shooterPos.y };
			Vector2 dir = Normalize(vec);
			bulletType[(int)BulletType::Single]->Fire(this, damage, m_bulletSpeed, dir);
		}
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

Vector2 CEnemy::SpawnOutScreen(Vector2 _scale)
{
	Vector2 screenSize = GameManager::GetInstance()->GetScreenSize();
	Vector2 pos;
	float marginX = _scale.x / 2.f + 50.f;
	float marginY = _scale.y / 2.f + 50.f;

	int side = rand() % 3; // 0: 위, 1: 왼쪽, 2: 오른쪽

	switch (side)
	{
	case 0: // 위쪽
		pos.x = static_cast<float>(rand() % static_cast<int>(screenSize.x));
		pos.y = -marginY;
		break;

	case 1: // 왼쪽
		pos.x = -marginX;
		pos.y = static_cast<float>(rand() % static_cast<int>(screenSize.y / 2.f));
		break;

	case 2: // 오른쪽
		pos.x = screenSize.x + marginX;
		pos.y = static_cast<float>(rand() % static_cast<int>(screenSize.y / 2.f));
		break;

	default:
		pos = Vector2{ 0.f, 0.f };
		break;
	}

	return pos;
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

	for (auto& iter : bulletType)
	{
		delete iter;
	}
 	bulletType.clear();
}

CActor* CEnemy::GetTarget()
{
	return target;
}

void CEnemy::SetTarget(Entity id)
{
	target = SceneManager::GetInstance()->GetCurrentScene()
		->GetSceneObjectList()->find(id)->second;
}

