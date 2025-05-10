#include "../../pch.h"
#include "../ComponentSystem.h"
#include "../04_Rigid/RigidbodySystem.h"
#include "TransformSystem.h"
#include "../../02.Component/Transform.h"
#include "../../02.Component/Rigidbody.h"

TransformSystem::TransformSystem(CObject* owner, Transform* transform) :
	m_transform(transform == nullptr ? new Transform{ Vector2{ 300.f,300.f }, 0.f, Vector2{ 30.f,30.f } } : transform)
{
	m_owner = owner;
	Speed = 30;
}

TransformSystem::~TransformSystem()
{
	delete m_transform;
}

void TransformSystem::Init()
{

}

void TransformSystem::Update(float _deltaTime)
{
	const Rigidbody& rigid = m_owner->GetComponent<RigidbodySystem>()->GetData();


	// 위치 갱신 (속도 적용)
	m_transform->position.x += rigid.velocity.x * Speed * _deltaTime;
	m_transform->position.y += rigid.velocity.y * Speed * _deltaTime;

	// 등록 이벤트 실행
	if (m_event)
		m_event();
}

const Transform& TransformSystem::GetData() const
{
	return *m_transform;
}
