#include "../../00_MainGame/MainGame.h"	
#include "../ComponentSystem.h"

#include "../../02_Component/Rigidbody.h"
#include "../../02_Component/InputData.h"
#include "RigidbodySystem.h"
#include "../03_Input/InputSystem.h"

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
