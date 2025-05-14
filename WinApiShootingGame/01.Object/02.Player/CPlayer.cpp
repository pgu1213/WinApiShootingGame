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

CPlayer::CPlayer() : inputManager(nullptr)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init(Entity id, EntityType type)
{
	CActor::Init(id, type);
	inputManager = new InputManager();
	inputManager->BindAxisKey(VK_LEFT, VK_RIGHT, "Horizontal");
	inputManager->BindAxisKey(VK_UP, VK_DOWN, "Vertical");
	inputManager->BindActionKey(VK_SPACE, "Shoot");

	Transform* transform = new Transform{ Vector2{ 300.f,300.f }, 0.f, Vector2{ 50.f,50.f } };
	TransformSystem* transformSystem = new TransformSystem(this, transform);
	Rigidbody* rigid = new Rigidbody();
	RigidbodySystem* rigidSystem = new RigidbodySystem(this, rigid);

	m_componentTable[typeid(RigidbodySystem)] = rigidSystem;
	m_componentTable[typeid(TransformSystem)] = transformSystem;
	m_componentTable[typeid(SpriteRendererSystem)] = new SpriteRendererSystem(this, GetDC(g_hWnd));

	render = dynamic_cast<IRenderer*>(m_componentTable[typeid(SpriteRendererSystem)]);

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

		rigid->velocity.x = inputManager->GetAxis("Horizontal") * 100.f;
		rigid->velocity.y = inputManager->GetAxis("Vertical") * 100.f;
	});
}

void CPlayer::Update(float DeltaTime)
{
	CActor::Update(DeltaTime);
	if (inputManager->GetKey("Shoot")) {
		// m_gameManager->SpawnBullet(m_id);
	}
}

void CPlayer::Render(HDC hdc)
{
	CActor::Render(hdc);
	render->Render(hdc);
}

void CPlayer::Release()
{
	CActor::Release();
}
