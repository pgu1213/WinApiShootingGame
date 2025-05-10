#include "../../pch.h"
#include "../ComponentSystem.h"
#include "../../02.Component/Rigidbody.h"
#include "RigidbodySystem.h"

RigidbodySystem::RigidbodySystem(MainGame* maingame, Entity id, Rigidbody* rigid) : m_rigidbody(rigid == nullptr ? new Rigidbody() : rigid)
{
	mainGame = maingame;
	m_id = id;
}

RigidbodySystem::~RigidbodySystem()
{
	delete m_rigidbody;
}

const Rigidbody& RigidbodySystem::GetData() const
{
	return *m_rigidbody;
}

void RigidbodySystem::Update()
{
	if (m_event) {
		m_event();
	}
}
