#include "../../99_Default/pch.h"
#include "../ComponentSystem.h"

#include "../../00_MainGame/MainGame.h"			// 매니저로 가져올 예정

#include "../04_Rigid/RigidbodySystem.h"
#include "TransformSystem.h"
#include "../../02_Component/Transform.h"
#include "../../02_Component/Rigidbody.h"

TransformSystem::TransformSystem(MainGame* maingame, Entity id, Transform* transform) : 
	m_transform(transform == nullptr ? new Transform{ Vector2{ 300.f,300.f }, 0.f, Vector2{ 30.f,30.f } } : transform)
{
	mainGame = maingame;
	m_id = id;
	Speed = 3;
}

TransformSystem::~TransformSystem()
{
	delete m_transform;
}

void TransformSystem::Update()
{
	const Rigidbody& rigid = mainGame->GetComponent<RigidbodySystem>(m_id)->GetData();

	// 위치 갱신 (속도 적용)
	m_transform->position.x += rigid.velocity.x * Speed;
	m_transform->position.y += rigid.velocity.y * Speed;
	
	// 등록 이벤트 실행
	if (m_event)
		m_event();
}

const Transform& TransformSystem::GetData() const
{
	return *m_transform;
}
