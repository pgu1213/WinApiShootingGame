#include "../../pch.h"
#include "CObject.h"

CObject::CObject() : m_bIsValid(true), m_type(EntityType::None), m_id(-1)
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
