#include "../../pch.h"
#include "CBoss1.h"

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

#include "../../01.Object/05.Scene/CScene.h"
#include "../03_Bullet/CBullet.h"
#include "../IBulletType.h"
#include "../98_BulletType/00.SingleBullet/SingleBullet.h"
#include "../98_BulletType/01.NWayBullet/NWayBullet.h"
#include "../98_BulletType/02.CircleBullet/CircleBullet.h"


#include "../../01.Object/IEnemyMove.h"
#include "../../01.Object/99_EnemyMove/RandomMove/EnemyMove_RandomMove.h"
#include "../../01.Object/99_EnemyMove/FixedPath/EnemyMove_FixedPathMove.h"
#include "../../01.Object/99_EnemyMove/Static/EnemyMove_StaticMove.h"

CBoss1::CBoss1()
{
	currentHP = 100;
	maxHP = currentHP;
	speed = 50.f;
	damage = 2;
	m_bulletSpeed = 250.f;
}

CBoss1::~CBoss1()
{
	Release();
}

void CBoss1::Init(Entity id, EntityType type)
{

	moveLogic = new EnemyMove_RandomMove(600.f,0,0,0,100);

	bulletType.resize((int)BulletType::None);

	bulletType[(int)BulletType::Single] = new SingleBullet();
	bulletType[(int)BulletType::NWay] = new NWayBullet(20.f, 8);
	bulletType[(int)BulletType::Circle] = new CircleBullet(12);

	Transform* transform = new Transform{ Vector2{ 0.f, 0.f }, 0.f, Vector2{ 250.f,250.f } };
	TransformSystem* transformSystem = new TransformSystem(this, transform);

	Rigidbody* rigid = new Rigidbody{ speed, speed };
	RigidbodySystem* rigidSystem = new RigidbodySystem(this, rigid);

	Collider* collider = new Collider{ ColliderType::Circle, {0.f, 0.f}, {0.f,0.f}, transform->scale.x /2.f -  40.f, transform->scale.y/2.f };

	ColliderSystem* colliderSystem = new ColliderSystem(this, collider);

	SpriteRendererSystem* spriteSystem = new SpriteRendererSystem(this, GetDC(g_hWnd));

	CoolTimeSystem* coolTimeSystem = new CoolTimeSystem(this);

	m_componentTable[typeid(CoolTimeSystem)] = coolTimeSystem;
	m_componentTable[typeid(RigidbodySystem)] = rigidSystem;
	m_componentTable[typeid(ColliderSystem)] = colliderSystem;
	m_componentTable[typeid(TransformSystem)] = transformSystem;
	m_componentTable[typeid(SpriteRendererSystem)] = spriteSystem;

	Vector2 screenSize = GameManager::GetInstance()->GetScreenSize();
	transform->position = Vector2{ screenSize.x / 2.f, 0.f - transform->scale.y };

	moveDestination = Vector2{ transform->position.x, transform->scale.y / 2.f };

	isEnteringScreen = true;

	CActor::Init(id, type);
  
	render = dynamic_cast<IRenderer*>(m_componentTable[typeid(SpriteRendererSystem)]);

	SpriteRenderer& playerSpriteData = spriteSystem->GetModifyData();
	playerSpriteData.filePath = L"05.Resource/01.Sprite/CBoss1.png";


	rigidSystem->AddEvent([=]() {
		Vector2 currentPos = transform->position;
  		Vector2 currentScale = transform->scale;

		float distToTarget = GetDistance(currentPos, moveDestination);
		if (distToTarget < 5.f && isMoveAble)
		{
			if (isEnteringScreen)	
				isEnteringScreen = false;
			
			if (moveLogic)
				moveDestination = moveLogic->GetNextPosition(currentPos, currentScale);
			isMoveAble = false;
		}

		if (!isMoveAble && distToTarget > 0.f)
			rigid->velocity = Vector2{ 0.0f, 0.0f };		
		else
			rigid->velocity = GetMoveTward(currentPos, moveDestination);
	});

	// 충돌 이벤트 등록: 총알에 맞으면 HP 감소
	colliderSystem->SetOnCollisionEvent([=](CActor* obj) {
		if (obj->GetType() == EntityType::PlayerBullet && !isEnteringScreen) {
			currentHP -= static_cast<CBullet*>(obj)->GetDamage();
			if (currentHP <= 0) {
				m_bIsValid = false;
				SceneManager::GetInstance()->GetCurrentScene()->AddRemoveVector(id);
			}
			SceneManager::GetInstance()->GetCurrentScene()->AddRemoveVector(obj->GetId());
		}
		});

	coolTimeSystem->AddTimer("shoot", 0.7f, [=]() {
		if (target != nullptr && !isEnteringScreen && bulletType.size() != 0) {
			Vector2 shooterPos = transform->position;
			Vector2 targetPos = target->GetComponent<TransformSystem>()->GetData().position;
			Vector2 vec = { targetPos.x - shooterPos.x , targetPos.y - shooterPos.y };
			Vector2 dir = Normalize(vec);
			bulletType[(int)BulletType::Single]->Fire(this, damage, m_bulletSpeed, dir);
		}
		coolTimeSystem->StartCooldown("shoot");
	});

	coolTimeSystem->AddTimer("NWayshoot", 2.5f, [=]() {
		if (target != nullptr && !isEnteringScreen && bulletType.size() != 0)
		{
			Vector2 dir = DistanceNormalize(transform->position, target->GetComponent<TransformSystem>()->GetData().position);

			bulletType[(int)BulletType::NWay]->Fire(this, damage, m_bulletSpeed, dir);
		}
		coolTimeSystem->StartCooldown("NWayshoot");
	});

	coolTimeSystem->AddTimer("CircleShoot", 6.f, [=]() {
		if (target != nullptr && !isEnteringScreen && bulletType.size() != 0)
		{
			Vector2 dir = DistanceNormalize(transform->position, target->GetComponent<TransformSystem>()->GetData().position);

			bulletType[(int)BulletType::Circle]->Fire(this, damage, m_bulletSpeed, dir);
		}
		coolTimeSystem->StartCooldown("CircleShoot");
	});

	coolTimeSystem->AddTimer("move", 1.f, [=]() {		
			isMoveAble = true;
		coolTimeSystem->StartCooldown("move");
	});

	coolTimeSystem->StartCooldown("shoot");
	coolTimeSystem->StartCooldown("move");
	coolTimeSystem->StartCooldown("NWayshoot");
	coolTimeSystem->StartCooldown("CircleShoot");
}


void CBoss1::Update(float DeltaTime)
{
	CEnemy::Update(DeltaTime);
}

void CBoss1::Release()
{
}

void CBoss1::Render(HDC hdc)
{
	CEnemy::Render(hdc);
}
