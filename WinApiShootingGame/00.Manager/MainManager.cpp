#include "../pch.h"
#include "MainManager.h"
#include "01.GameManager/GameManager.h"
#include "03.TimeManager/TimeManager.h"
#include "06.ResourceManager/ResourceManager.h"

MainManager::MainManager()
{
}

MainManager::~MainManager()
{
}

// 하위 매니저들의 Init을 담당
void MainManager::Init()
{
	if (!TimeManager::GetInstance()->Init())
	{
		return;
	}

	if (!ResourceManager::GetInstance()->Init())
	{
		return;
	}

	GameManager::GetInstance()->Init();
}

// 늦게 Init되어야 하는 것들
void MainManager::LateInit()
{
	ResourceManager::GetInstance()->LoadSprite(L"05.Resource/01.Sprite/Fly.png");
}

void MainManager::Update()
{
	TimeManager::GetInstance()->Update(); // 매 프레임마다 호출하여 델타 시간 업데이트

	float DeltaTime = TimeManager::GetInstance()->GetDeltaTime(); // 현재 프레임의 델타 시간 가져오기

	GameManager::GetInstance()->Update(DeltaTime); // 게임 매니저 업데이트
}

void MainManager::Render(HDC hdc)
{
	GameManager::GetInstance()->Render(hdc); // 게임 매니저 렌더링
}
