#include "../../pch.h"
#include "CObject.h"
#include "../../00.Manager/01.GameManager/GameManager.h"
#include "../../03.System/ComponentSystem.h"
#include "../../00.Manager/03.TimeManager/TimeManager.h"

CObject::CObject() : m_bIsValid(true)
{

}

CObject::~CObject()
{

}

void CObject::Init(Entity id, EntityType type)
{
	m_id = id;
	m_type = type;
}

void CObject::Update(float DeltaTime)
{
	for (auto& comp : m_componentTable)
	{
		comp.second->Update(DeltaTime);		
	}
}

void CObject::Render(HDC hdc)
{
	for (auto& comp : m_componentTable)
	{
		comp.second->Render(hdc);
	}
}

void CObject::Release()
{
}

const Entity& CObject::GetId() const
{
	return m_id;
}

const EntityType& CObject::GetType() const
{
	return m_type;
}


bool CObject::IsValid() const
{
	return false;
}
