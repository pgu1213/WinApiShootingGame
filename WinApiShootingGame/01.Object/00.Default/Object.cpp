#include "../../pch.h"
#include "Object.h"
#include "../../00.Manager/03.TimeManager/TimeManager.h"

Object::Object(const string& Name) : ObjectID(NextObjectID++), ObjectName(Name), bIsValid(true)
{

}

void Object::Init()
{
}

void Object::Update(float DeltaSeconds)
{
}

void Object::Release()
{
}

unsigned int Object::GetObjectID() const
{
	return 0;
}

const string& Object::GetObjectName() const
{
	return ObjectName;
}

bool Object::IsValid() const
{
	return false;
}
