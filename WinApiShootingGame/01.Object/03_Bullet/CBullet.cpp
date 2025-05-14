#include "../../pch.h"
#include "CBullet.h"
#include "../../00.Manager/01.GameManager/GameManager.h"

#include "../../03.System/ComponentSystem.h"
#include "../../03.System/00_Transform/TransformSystem.h"
#include "../../03.System/01_SpriteRenderer/SpriteRendererSystem.h""
#include "../../03.System/04_Rigid/RigidbodySystem.h"
#include "../../03.System/02_Collider/ColliderSystem.h"

#include "../../02.Component/Transform.h"
#include "../../02.Component/SpriteRenderer.h"
#include "../../02.Component/Collider.h"
#include "../../02.Component/Rigidbody.h"

CBullet::CBullet(CActor& _posTarget) : posTarget(_posTarget)
{
}

CBullet::~CBullet()
{
}

void CBullet::Init(Entity id, EntityType type)
{
	CActor::Init(id, type);
	GameManager* mgr = GameManager::GetInstance();

	const Transform& shooterTransform = posTarget.GetComponent<TransformSystem>()->GetData();

	Transform* transform = new Transform{ shooterTransform.position, 0.f, Vector2{30.f, 30.f} };
	Rigidbody* rigid = new Rigidbody{ Vector2{0.f, -100.f} };
	Collider* collider = new Collider{ {0.f, 0.f}, transform->scale };

	TransformSystem* transformSystem = new TransformSystem(this, transform);
	RigidbodySystem* rigidSystem = new RigidbodySystem(this, rigid);
	SpriteRendererSystem* spriteSystem = new SpriteRendererSystem(this, GetDC(g_hWnd));
	ColliderSystem* colliderSystem = new ColliderSystem(this, collider);

	m_componentTable[typeid(TransformSystem)] = transformSystem;
	m_componentTable[typeid(ColliderSystem)] = colliderSystem;
	m_componentTable[typeid(RigidbodySystem)] = rigidSystem;
	m_componentTable[typeid(SpriteRendererSystem)] = spriteSystem;

	render = dynamic_cast<IRenderer*>(m_componentTable[typeid(SpriteRendererSystem)]);

	Vector2 screenSize = GameManager::GetScreenSize();

	transformSystem->AddEvent([=]() {
		const Transform& transform = transformSystem->GetData();
		if (transform.position.y < 0 || transform.position.y > screenSize.y) {
			mgr->AddRemoveVector(id);
		}
		});

	colliderSystem->SetOnCollisionEvent([=](CObject* obj) {
		EntityType type = obj->GetType();
		EntityType bulletType = obj->GetType();
		if ((type == EntityType::Enemy && bulletType == EntityType::PlayerBullet) || (type == EntityType::Player && bulletType == EntityType::EnemyBullet)) {
			mgr->AddRemoveVector(id);
		}
		});

}

void CBullet::Update(float DeltaTime)
{
	CActor::Update(DeltaTime);
}

void CBullet::Render(HDC hdc)
{
	CActor::Render(hdc);
	render->Render(hdc);
}

void CBullet::Release()
{
	CActor::Release();
}
