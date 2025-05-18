#include "../../pch.h"
#include "CBullet.h"
#include "../../00.Manager/01.GameManager/GameManager.h"
#include "../../00.Manager/02.SceneManager/SceneManager.h"
#include "../../01.Object/05.Scene/CScene.h"

#include "../../03.System/ComponentSystem.h"
#include "../../03.System/00_Transform/TransformSystem.h"
#include "../../03.System/01_SpriteRenderer/SpriteRendererSystem.h""
#include "../../03.System/03_Rigid/RigidbodySystem.h"
#include "../../03.System/02_Collider/ColliderSystem.h"

#include "../../02.Component/Transform.h"
#include "../../02.Component/SpriteRenderer.h"
#include "../../02.Component/Collider.h"
#include "../../02.Component/Rigidbody.h"

CBullet::CBullet(CActor& _shooter, float _damage, float _speed) : m_shooter(_shooter), m_damage(_damage), m_speed(_speed)
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Init(Entity id, EntityType type)
{
	const Transform& shooterTransform = m_shooter.GetComponent<TransformSystem>()->GetData();

	Transform* transform = new Transform{ shooterTransform.position, 0.f, Vector2{30.f, 30.f} };
	Rigidbody* rigid = new Rigidbody{ Vector2{m_speed, m_speed} };
	Collider* collider = new Collider{ ColliderType::Circle, {0.f, 0.f}, {0.f,0.f}, 30.f / 2.f, 30.f /2.f};

	TransformSystem* transformSystem = new TransformSystem(this, transform);
	RigidbodySystem* rigidSystem = new RigidbodySystem(this, rigid);
	SpriteRendererSystem* spriteSystem = new SpriteRendererSystem(this, GetDC(g_hWnd));
	ColliderSystem* colliderSystem = new ColliderSystem(this, collider);

	m_componentTable[typeid(TransformSystem)] = transformSystem;
	m_componentTable[typeid(ColliderSystem)] = colliderSystem;
	m_componentTable[typeid(RigidbodySystem)] = rigidSystem;
	m_componentTable[typeid(SpriteRendererSystem)] = spriteSystem;

	CActor::Init(id, type);

	render = dynamic_cast<IRenderer*>(m_componentTable[typeid(SpriteRendererSystem)]);

	SpriteRenderer& bulletSpriteData = spriteSystem->GetModifyData();
	if (type == EntityType::PlayerBullet)
		bulletSpriteData.filePath = L"05.Resource/01.Sprite/PlayerBullet.png";
	else
		bulletSpriteData.filePath = L"05.Resource/01.Sprite/EnemyBullet.png";

	transformSystem->AddEvent([=]() {
		const Transform& transform = transformSystem->GetData();
		if (transform.position.y < 0 || transform.position.y > GameManager::GetScreenSize().y) {
			SceneManager::GetInstance()->GetCurrentScene()->AddRemoveVector(id);
		}
		});

	colliderSystem->SetOnCollisionEvent([=](CObject* obj) {
		if ((obj->GetType() == EntityType::Enemy && m_type == EntityType::PlayerBullet) || (obj->GetType() == EntityType::Player && m_type == EntityType::EnemyBullet)) {
			SceneManager::GetInstance()->GetCurrentScene()->AddRemoveVector(id);
		}
		});

}

void CBullet::Update(float DeltaTime)
{
	CActor::Update(DeltaTime);
}

void CBullet::Render(HDC hdc)
{
	render->Render(hdc);
}


void CBullet::Release()
{
}

void CBullet::SetBulletDirection(Vector2 _dir)
{
	Vector2 vel = Vector2{ _dir.x * m_speed, _dir.y * m_speed };
	Rigidbody* rigid = new Rigidbody{ vel };
	GetComponent<RigidbodySystem>()->GetData() = *rigid;
}
float CBullet::GetDamage()
{
	return m_damage;
}
