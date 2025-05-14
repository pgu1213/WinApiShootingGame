#include "../../pch.h"
#include "CActor.h"
#include "../../00.Manager/01.GameManager/GameManager.h"
#include "../../03.System/ComponentSystem.h"
#include "../../00.Manager/03.TimeManager/TimeManager.h"

CActor::CActor() : render(nullptr)
{
}

CActor::~CActor()
{
	Release();
}

void CActor::Init(Entity id, EntityType type)
{
	m_id = id;
	m_type = type;
}

void CActor::Update(float DeltaTime)
{
	for (auto& comp : m_componentTable)
	{
		comp.second->Update(DeltaTime);
	}
}

void CActor::Render(HDC hdc)
{
}

void CActor::Release()
{
}
