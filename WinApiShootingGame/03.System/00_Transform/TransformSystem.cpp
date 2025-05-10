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
	Speed = 3;	
	m_rigidbody = &m_owner->GetComponent<RigidbodySystem>()->GetData();
}

TransformSystem::~TransformSystem()
{
	delete m_transform;
}

void TransformSystem::Update(float _deltaTime)
{
	// 위치 갱신 (속도 적용)
	m_transform->position.x += m_rigidbody->velocity.x * Speed * _deltaTime;
	m_transform->position.y += m_rigidbody->velocity.y * Speed * _deltaTime;
	
	// 등록 이벤트 실행
	if (m_event)
		m_event();
}

const Transform& TransformSystem::GetData() const
{
	return *m_transform;
}
