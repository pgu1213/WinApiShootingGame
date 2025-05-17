#include "../../pch.h"
#include "../../03.System/ComponentSystem.h"
#include "../../02.Component/CoolTime.h"
#include "CoolTimeSystem.h"

CoolTimeSystem::CoolTimeSystem(CActor* owner)
{
	m_owner = owner;
	/*m_lastUpdateTime = GetTickCount64();*/
}

CoolTimeSystem::~CoolTimeSystem()
{

}

void CoolTimeSystem::Init()
{
}

void CoolTimeSystem::AddTimer(const string& key, float coolTime, function<void()> onComplete)
{
    Timer timer;
    timer.coolTime = coolTime;
    timer.currentTime = 0.0f;
    timer.isActive = false;
    timer.onCompleteEvent = onComplete;

    timerMap[key] = timer;
}

void CoolTimeSystem::StartCooldown(const std::string& key)
{
    auto it = timerMap.find(key);
    if (it != timerMap.end())
    {
        it->second.currentTime = 0.0f;
        it->second.isActive = true;
    }
}

void CoolTimeSystem::Update(float deltaTime)
{
    for (auto& [key, timer] : timerMap)
    {
        if (!timer.isActive)
            continue;

        timer.currentTime += deltaTime;

        if (timer.currentTime >= timer.coolTime)
        {
            timer.isActive = false;
            timer.currentTime = timer.coolTime;

            if (timer.onCompleteEvent)
                timer.onCompleteEvent();
        }
    }
}


