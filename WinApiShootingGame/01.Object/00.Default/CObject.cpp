#include "../../pch.h"
#include "CObject.h"
#include "../../00.Manager/01.GameManager/GameManager.h"
#include "../../03.System/ComponentSystem.h"
#include "../../00.Manager/03.TimeManager/TimeManager.h"

CObject::CObject(const string& Name) : /*m_ObjectID(m_NextObjectID++), */ m_ObjectName(Name), m_bIsValid(true)
{

}

void CObject::Init(Entity id, ComponentTable compTable)
{
	m_id = id;
	m_componentTable = compTable;
}

void CObject::Update(float DeltaTime)
{
	for (auto comp : m_componentTable)
	{
		ComponentSystem* system = comp.second;
		system->Update(DeltaTime);
	}
}

void CObject::Release()
{
}

//unsigned int CObject::GetObjectID() const
//{
//	return m_ObjectID;
//}

const Entity& CObject::GetId() const
{
	return m_id;
}

const string& CObject::GetObjectName() const
{
	return m_ObjectName;
}

bool CObject::IsValid() const
{
	return false;
}
