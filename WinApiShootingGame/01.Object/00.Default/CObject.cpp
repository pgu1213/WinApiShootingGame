#include "../../pch.h"
#include "CObject.h"
#include "../../00.Manager/03.TimeManager/TimeManager.h"

CObject::CObject(const string& Name) : m_ObjectID(m_NextObjectID++), m_ObjectName(Name), m_bIsValid(true)
{

}

void CObject::Init()
{
}

void CObject::Update(float DeltaTime)
{
}

void CObject::Release()
{
}

unsigned int CObject::GetObjectID() const
{
	return m_ObjectID;
}

const string& CObject::GetObjectName() const
{
	return m_ObjectName;
}

bool CObject::IsValid() const
{
	return false;
}
