#include "../pch.h"
#include "MainManager.h"
#include "03.TimeManager/TimeManager.h"

MainManager::MainManager()
{
}

MainManager::~MainManager()
{
}

void MainManager::Init()
{
    if (!TimeManager::Init())
    {
        return;
    }
}

void MainManager::LateInit()
{
}

void MainManager::Update()
{
	TimeManager::GetInstance()->Update(); // 매 프레임마다 호출하여 델타 시간 업데이트

	float DeltaTime = TimeManager::GetInstance()->GetDeltaTime(); // 현재 프레임의 델타 시간 가져오기

}

void MainManager::Render(HDC hdc)
{

}
