#include "../../pch.h"
#include "Object.h"
#include "../../00.Manager/03.TimeManager/TimeManager.h"

Object::Object(const std::string& Name) : ObjectID(NextObjectID++), ObjectName(Name), bIsValid(true)
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

const std::string& Object::GetObjectName() const
{
	// TODO: 여기에 return 문을 삽입합니다.
}

bool Object::IsValid() const
{
	return false;
}
