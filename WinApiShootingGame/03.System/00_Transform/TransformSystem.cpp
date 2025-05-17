#include "../../pch.h"
#include "../ComponentSystem.h"
#include "TransformSystem.h"
#include "../03_Rigid/RigidbodySystem.h"
#include "../../02.Component/Transform.h"
#include "../../02.Component/Rigidbody.h"

TransformSystem::TransformSystem(CActor* owner, Transform* transform) :
	m_transform(transform), rigid(nullptr)
{
	m_owner = owner;

}

TransformSystem::~TransformSystem()
{
	delete m_transform;
}

void TransformSystem::Init()
{
	rigid = &m_owner->GetComponent<RigidbodySystem>()->GetData();
}

void TransformSystem::Update(float _deltaTime)
{	
	// 위치 갱신 (속도 적용)
	m_transform->position.x += rigid->velocity.x * _deltaTime;
	m_transform->position.y += rigid->velocity.y * _deltaTime;

	// 등록 이벤트 실행
	if (m_event)
		m_event();
}

Transform& TransformSystem::GetData() const
{
	return *m_transform;
}


void TransformSystem::operator=(Transform& trans)
{
	delete m_transform;
	m_transform = nullptr;
	m_transform = &trans;
}
