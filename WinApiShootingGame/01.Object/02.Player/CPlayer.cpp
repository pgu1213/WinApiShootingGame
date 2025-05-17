#include "../../pch.h"
#include "CPlayer.h"
#include "../../00.Manager/01.GameManager/GameManager.h"
#include "../../00.Manager/04.InputManager/InputManager.h"

#include "../../03.System/ComponentSystem.h"

#include "../../03.System/00_Transform/TransformSystem.h"
#include "../../03.System/01_SpriteRenderer/SpriteRendererSystem.h""
#include "../../03.System/03_Rigid/RigidbodySystem.h"
#include "../../03.System/02_Collider/ColliderSystem.h"

#include "../../02.Component/Transform.h"
#include "../../02.Component/SpriteRenderer.h"
#include "../../02.Component/Collider.h"
#include "../../02.Component/Rigidbody.h"

#include "../03_Bullet/CBullet.h"

CPlayer::CPlayer() : m_inputManager(nullptr), m_transform(nullptr), currentHP(3), maxHP(3), speed(300.f), damage(1)
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

	Transform* transform = new Transform{ Vector2{ 300.f,300.f }, 0.f, Vector2{ 50.f,50.f } };
	TransformSystem* transformSystem = new TransformSystem(this, transform);

	Rigidbody* rigid = new Rigidbody{ Vector2{0.f,0.f} };
	RigidbodySystem* rigidSystem = new RigidbodySystem(this, rigid);

	SpriteRendererSystem* spriteSystem = new SpriteRendererSystem(this, GetDC(g_hWnd));
	
	Collider* col = new Collider{ Vector2{0,0} , Vector2{40.f, 40.f} };
	ColliderSystem* colliderSystem = new ColliderSystem(this, col);

	m_componentTable[typeid(ColliderSystem)] = colliderSystem;
	m_componentTable[typeid(RigidbodySystem)] = rigidSystem;
	m_componentTable[typeid(TransformSystem)] = transformSystem;
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

	colliderSystem->SetOnCollisionEvent([=](CActor* obj) {
		if (obj->GetType() == EntityType::EnemyBullet) {
			currentHP -= static_cast<CBullet*>(obj)->GetDamage();
			if (currentHP <= 0) {
				m_bIsValid = false;
				GameManager::GetInstance()->AddRemoveVector(id);
			}
			GameManager::GetInstance()->AddRemoveVector(obj->GetId());
		}
		});

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
}

void CPlayer::Update(float DeltaTime)
{
	CActor::Update(DeltaTime);
	if (m_inputManager->GetKey("Shoot")) {
 		GameManager::GetInstance()->SpawnBullet(m_id, damage);
	}
}

void CPlayer::Render(HDC hdc)
{
	render->Render(hdc);
}

void CPlayer::Release()
{
	delete m_inputManager;
}
