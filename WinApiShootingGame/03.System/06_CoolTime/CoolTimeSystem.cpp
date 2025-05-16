#include "../../pch.h"
#include "../../03.System/ComponentSystem.h"
#include "../../02.Component/CoolTime.h"
#include "CoolTimeSystem.h"

 CoolTime& CoolTimeSystem::GetData() const
{
	return *m_coolTime;
}

CoolTimeSystem::CoolTimeSystem(CActor* owner, CoolTime* coolTime) :m_coolTime(coolTime), isActive(false)
{
	m_owner = owner;
	m_lastUpdateTime = GetTickCount64();
}

CoolTimeSystem::~CoolTimeSystem()
{
	delete m_coolTime;
}

void CoolTimeSystem::Init()
{
}

void CoolTimeSystem::StartCooldown()
{
	m_coolTime->currentTime = 0.0f;
	m_lastUpdateTime = GetTickCount64();
	isActive = true;
}

bool CoolTimeSystem::CheckActive()
{
	return isActive;
}

void CoolTimeSystem::Update(float _deltaTime)
{
	
	if (!isActive)
		return;

	float now = GetTickCount64();
	float delta = _deltaTime;
	m_lastUpdateTime = now;

	m_coolTime->currentTime += delta;

	if (m_coolTime->currentTime > m_coolTime->coolTime)
	{
		m_coolTime->currentTime = m_coolTime->coolTime;
		isActive = false;

		if (m_event)
			m_event();
	}
}


