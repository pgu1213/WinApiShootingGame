#include "../../pch.h"
#include "GameManager.h"
#include "../03.TimeManager/TimeManager.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

// 씬 관련 설정
bool GameManager::Init()
{
    /*
    CurrentScene = new Scene(); 씬 객체 생성
    if (!CurrentScene)
    {
        return false;
    }
    CurrentScene->Init();
    */

    // Object::Init();

    return true;
}

// 씬을 Update 하기 위함
void GameManager::Update(float DeltaTime)
{
	if (DeltaTime < 0.0f)
	{
		return; // 델타 시간이 유효하지 않으면 업데이트 하지 않음
	}

    // TODO - 씬 업데이트
}
