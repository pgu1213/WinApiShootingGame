#include "../../pch.h"
#include "CPlayer.h"
#include "../../00.Manager/01.GameManager/GameManager.h"
#include "../../00.Manager/04.InputManager/InputManager.h"

#include "../../03.System/ComponentSystem.h"

#include "../../03.System/00_Transform/TransformSystem.h"
#include "../../03.System/01_SpriteRenderer/SpriteRendererSystem.h""
#include "../../03.System/03_Rigid/RigidbodySystem.h"
#include "../../03.System/02_Collider/ColliderSystem.h"
#include "../../03.System/04_CoolTime/CoolTimeSystem.h"

#include "../../02.Component/Transform.h"
#include "../../02.Component/SpriteRenderer.h"
#include "../../02.Component/Collider.h"
#include "../../02.Component/Rigidbody.h"

#include "../03_Bullet/CBullet.h"
#include "../IBulletType.h"
#include "../../01.Object/98_BulletType/00.SingleBullet/SingleBullet.h"

CPlayer::CPlayer() : m_inputManager(nullptr), bulletType(nullptr), currentHP(4), maxHP(3), speed(300.f), damage(1), m_direction(Vector2{ 0.f, 1.f }), bulletSpeed(-200.f), attackAble(true)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Init(Entity id, EntityType type)
{
	m_inputManager = new InputManager();
	m_inputManager->BindAxisKey(VK_LEFT, VK_RIGHT, "Horizontal");
	m_inputManager->BindAxisKey(VK_UP, VK_DOWN, "Vertical");
	m_inputManager->BindActionKey(VK_SPACE, "Shoot");

	bulletType = new SingleBullet();

	Transform* transform = new Transform{ Vector2{ 300.f,300.f }, 0.f, Vector2{ 50.f,50.f } };
	TransformSystem* transformSystem = new TransformSystem(this, transform);

	Rigidbody* rigid = new Rigidbody{ Vector2{0.f,0.f} };
	RigidbodySystem* rigidSystem = new RigidbodySystem(this, rigid);

	SpriteRendererSystem* spriteSystem = new SpriteRendererSystem(this, GetDC(g_hWnd));

	Collider* collider = new Collider{ ColliderType::Circle, {0.f, 0.f}, {0.f,0.f}, transform->scale.x / 2.f,transform->scale.y /2.f};

	ColliderSystem* colliderSystem = new ColliderSystem(this, collider);

	CoolTimeSystem* coolTimeSystem = new CoolTimeSystem(this);

	m_componentTable[typeid(ColliderSystem)] = colliderSystem;
	m_componentTable[typeid(RigidbodySystem)] = rigidSystem;
	m_componentTable[typeid(TransformSystem)] = transformSystem;
	m_componentTable[typeid(CoolTimeSystem)] = coolTimeSystem;
	m_componentTable[typeid(SpriteRendererSystem)] = spriteSystem;

	CActor::Init(id, type);

	render = dynamic_cast<IRenderer*>(m_componentTable[typeid(SpriteRendererSystem)]);

	SpriteRenderer& playerSpriteData = spriteSystem->GetModifyData();
	playerSpriteData.filePath = L"05.Resource/01.Sprite/Fly.png";

	transformSystem->AddEvent([=]() {
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
	});

	//colliderSystem->SetOnCollisionEvent([=](CActor* obj) {
	//	if (obj->GetType() == EntityType::EnemyBullet) {
	//		currentHP -= static_cast<CBullet*>(obj)->GetDamage();
	//		if (currentHP <= 0) {
	//			m_bIsValid = false;
	//			GameManager::GetInstance()->AddRemoveVector(id);
	//		}
	//		GameManager::GetInstance()->AddRemoveVector(obj->GetId());
	//	}
	//	});

	rigidSystem->AddEvent([=]() {

		float inputX = m_inputManager->GetAxis("Horizontal");
		float inputY = m_inputManager->GetAxis("Vertical");

		Vector2 inputVec = { inputX, inputY };

		if (inputVec.x != 0 || inputVec.y != 0) {
			inputVec = Normalize(inputVec);
		}

		rigid->velocity.x = inputVec.x * speed;
		rigid->velocity.y = inputVec.y * speed;
	});

	coolTimeSystem->AddTimer("shoot", 0.3f, [=]() {
		attackAble = true;
		coolTimeSystem->StartCooldown("shoot");
		});

	coolTimeSystem->StartCooldown("shoot");
}

void CPlayer::Update(float DeltaTime)
{
	CActor::Update(DeltaTime);
	if (m_inputManager->GetKey("Shoot")) {
		if (bulletType && attackAble) {
			bulletType->Fire(this, damage, bulletSpeed, m_direction);
			attackAble = false;
		}
	}
}

void CPlayer::Render(HDC hdc)
{
	render->Render(hdc);
}

void CPlayer::Release()
{
	delete m_inputManager;
	delete bulletType;
}

void CPlayer::SetBulletPattern(IBulletType* pattern)
{
	if (bulletType) delete bulletType;
	bulletType = pattern;
}

