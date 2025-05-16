#include "../../pch.h"
#include "CEnemy.h"
#include "../../00.Manager/01.GameManager/GameManager.h"

#include "../../03.System/ComponentSystem.h"
#include "../../03.System/00_Transform/TransformSystem.h"
#include "../../03.System/01_SpriteRenderer/SpriteRendererSystem.h""
#include "../../03.System/04_Rigid/RigidbodySystem.h"
#include "../../03.System/02_Collider/ColliderSystem.h"
#include "../../03.System/05_State/StateSystem.h"
#include "../../03.System/06_CoolTime/CoolTimeSystem.h"

#include "../../02.Component/Transform.h"
#include "../../02.Component/SpriteRenderer.h"
#include "../../02.Component/Collider.h"
#include "../../02.Component/Rigidbody.h"
#include "../../02.Component/State.h"
#include "../../02.Component/CoolTime.h"

void CEnemy::Init(Entity id, EntityType type)
{
	CActor::Init(id, type);

	Transform* transform = new Transform{ Vector2{ 100.f,100.f }, 0.f, Vector2{ 50.f,50.f } };
	TransformSystem* transformSystem = new TransformSystem(this, transform);

	Rigidbody* rigid = new Rigidbody();
	RigidbodySystem* rigidSystem = new RigidbodySystem(this, rigid);

	Collider* collider = new Collider{ {0.f, 0.f}, transform->scale };
	ColliderSystem* colliderSystem = new ColliderSystem(this, collider);

	SpriteRendererSystem* spriteSystem = new SpriteRendererSystem(this, GetDC(g_hWnd));

	State* state = new State{ 3, 3, 0 };
	StateSystem* stateSystem = new StateSystem(this, state);

	CoolTime* coolTime = new CoolTime{ 0.f , 3.f };
	CoolTimeSystem* coolTimeSystem = new CoolTimeSystem(this, coolTime);

	m_componentTable[typeid(CoolTimeSystem)] = coolTimeSystem;
	m_componentTable[typeid(RigidbodySystem)] = rigidSystem;
	m_componentTable[typeid(ColliderSystem)] = colliderSystem;
	m_componentTable[typeid(TransformSystem)] = transformSystem;
	m_componentTable[typeid(SpriteRendererSystem)] = spriteSystem;
	m_componentTable[typeid(StateSystem)] = stateSystem;

	render = dynamic_cast<IRenderer*>(m_componentTable[typeid(SpriteRendererSystem)]);

	SpriteRenderer& playerSpriteData = spriteSystem->GetModifyData();
	playerSpriteData.filePath = L"05.Resource/01.Sprite/EnemyTest.png";


	// 충돌 이벤트 등록: 총알에 맞으면 HP 감소
	colliderSystem->SetOnCollisionEvent([=](CObject* obj) {
		if (obj->GetType() == EntityType::PlayerBullet) {
			stateSystem->TakeDamage(1);
			if (stateSystem->IsDead()) {
				GameManager::GetInstance()->AddRemoveVector(id);
			}
			GameManager::GetInstance()->AddRemoveVector(obj->GetId());
		}
		});

	coolTimeSystem->AddEvent([=]() {
		Vector2 enemyPos = transform->position;
		Vector2 playerPos = target->GetComponent<TransformSystem>()->GetData().position;
		Vector2 vec = { playerPos.x - enemyPos.x , playerPos.y - enemyPos.y };
		Vector2 dir = Normalize(vec);
		Vector2 vel = Vector2{ dir.x * 80.f, dir.y * 80.f };

	 GameManager::GetInstance()->SpawnBullet(id, enemyPos, vel);
		// Bullet 생성 함수 호출
		coolTimeSystem->StartCooldown(); // 쿨타임 재시작
		});

	coolTimeSystem->StartCooldown();
}

void CEnemy::Update(float DeltaTime)
{
	CActor::Update(DeltaTime);
}

void CEnemy::Render(HDC hdc)
{
	CActor::Render(hdc);
	render->Render(hdc);
}

void CEnemy::Release()
{
}

CActor* CEnemy::GetTarget()
{
	return target;
}

void CEnemy::SetTarget(Entity id)
{
	target= GameManager::GetInstance()
		->GetEntityTable()->find(id)->second;	
}

Vector2 CEnemy::Normalize(Vector2 v)
{
	float len = sqrt(v.x * v.x + v.y * v.y);
	return (len != 0) ? Vector2{ v.x / len, v.y / len } : Vector2{ 0.f, 0.f };
}
