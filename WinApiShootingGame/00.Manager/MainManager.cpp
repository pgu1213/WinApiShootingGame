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
    TimeManager::Update();

    float DeltaTime = TimeManager::GetDeltaTime();

    // mainGame->Update(DeltaTime);
    // mainGame->Render(); // 렌더링에서도 필요하다면 DeltaTime 활용
}

void MainManager::Render(HDC hdc)
{

}
