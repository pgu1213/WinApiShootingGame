#include "../../pch.h"
#include "../ComponentSystem.h"
#include "../../02.Component/Rigidbody.h"
#include "RigidbodySystem.h"

RigidbodySystem::RigidbodySystem(CActor* owner,Rigidbody* rigid) : m_rigidbody(rigid == nullptr ? new Rigidbody() : rigid)
{
	m_owner = owner;
}

RigidbodySystem::~RigidbodySystem()
{
	delete m_rigidbody;
}

void RigidbodySystem::Init()
{
}

const Rigidbody& RigidbodySystem::GetData() const
{
	return *m_rigidbody;
}

void RigidbodySystem::Update(float _deltaTime)
{
	if (m_event) {
		m_event();
	}
}
