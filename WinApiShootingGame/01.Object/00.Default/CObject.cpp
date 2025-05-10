#include "../../pch.h"
#include "CObject.h"
#include "../../00.Manager/03.TimeManager/TimeManager.h"

CObject::CObject(const string& Name) : ObjectID(NextObjectID++), ObjectName(Name), bIsValid(true)
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
	return ObjectID;
}

const string& CObject::GetObjectName() const
{
	return ObjectName;
}

bool CObject::IsValid() const
{
	return false;
}
