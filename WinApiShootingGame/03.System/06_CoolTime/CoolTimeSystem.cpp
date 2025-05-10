#include "../../99_Default/pch.h"
#include "../../00_MainGame/MainGame.h"
#include "../../01_System/ComponentSystem.h"
#include "../../02_Component/CoolTime.h"
#include "CoolTimeSystem.h"

const CoolTime& CoolTimeSystem::GetData() const
{
	return *m_coolTime;
}

CoolTimeSystem::CoolTimeSystem(MainGame* maingame ,Entity id, CoolTime* coolTime) :m_coolTime(coolTime), isActive(false)
{
	mainGame = maingame;
	m_id = id;
	m_lastUpdateTime = GetTickCount64();
}

CoolTimeSystem::~CoolTimeSystem()
{
	delete m_coolTime;
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

void CoolTimeSystem::Update()
{
	
	if (!isActive)
		return;

	float now = GetTickCount64();
	float delta = (now - m_lastUpdateTime) / 1000.0f; // ÃÊ ´ÜÀ§
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


