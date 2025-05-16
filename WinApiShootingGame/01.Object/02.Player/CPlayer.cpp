#include "../../pch.h"
#include "CPlayer.h"
#include "../../00.Manager/01.GameManager/GameManager.h"
#include "../../00.Manager/04.InputManager/InputManager.h"

#include "../../03.System/ComponentSystem.h"
#include "../../03.System/00_Transform/TransformSystem.h"
#include "../../03.System/01_SpriteRenderer/SpriteRendererSystem.h""
#include "../../03.System/04_Rigid/RigidbodySystem.h"
#include "../../03.System/02_Collider/ColliderSystem.h"

#include "../../02.Component/Transform.h"
#include "../../02.Component/SpriteRenderer.h"
#include "../../02.Component/Collider.h"
#include "../../02.Component/Rigidbody.h"

CPlayer::CPlayer() : m_inputManager(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Init(Entity id, EntityType type)
{
	CActor::Init(id, type);
	m_inputManager = new InputManager();
	m_inputManager->BindAxisKey(VK_LEFT, VK_RIGHT, "Horizontal");
	m_inputManager->BindAxisKey(VK_UP, VK_DOWN, "Vertical");
	m_inputManager->BindActionKey(VK_SPACE, "Shoot");

	Transform* transform = new Transform{ Vector2{ 300.f,300.f }, 0.f, Vector2{ 50.f,50.f } };
	TransformSystem* transformSystem = new TransformSystem(this, transform);

	Rigidbody* rigid = new Rigidbody();
	RigidbodySystem* rigidSystem = new RigidbodySystem(this, rigid);

	SpriteRendererSystem* spriteSystem = new SpriteRendererSystem(this, GetDC(g_hWnd));
	
	Collider* col = new Collider{ Vector2{0,0} , Vector2{40.f, 40.f} };
	ColliderSystem* colSystem = new ColliderSystem(this, col);

	m_componentTable[typeid(ColliderSystem)] = colSystem;
	m_componentTable[typeid(RigidbodySystem)] = rigidSystem;
	m_componentTable[typeid(TransformSystem)] = transformSystem;
	m_componentTable[typeid(SpriteRendererSystem)] = spriteSystem;

	render = dynamic_cast<IRenderer*>(m_componentTable[typeid(SpriteRendererSystem)]);

	SpriteRenderer& playerSpriteData = spriteSystem->GetModifyData();
	playerSpriteData.filePath = L"05.Resource/01.Sprite/Fly.png";

	Vector2 screenSize = GameManager::GetScreenSize();

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

		rigid->velocity.x = m_inputManager->GetAxis("Horizontal") * 100.f;
		rigid->velocity.y = m_inputManager->GetAxis("Vertical") * 100.f;
	});
}

void CPlayer::Update(float DeltaTime)
{
	CActor::Update(DeltaTime);
	if (m_inputManager->GetKey("Shoot")) {
 		GameManager::GetInstance()->SpawnBullet(m_id);
	}
}

void CPlayer::Render(HDC hdc)
{
	CActor::Render(hdc);
	render->Render(hdc);
}

void CPlayer::Release()
{
	delete m_inputManager;
}
