#include "../../pch.h"
#include "GameManager.h"
#include "../03.TimeManager/TimeManager.h"

bool GameManager::Init()
{
    if (!TimeManager::Init())
    {
        return false; // 초기화 실패
    }

    /*
    CurrentScene = new Scene(); 씬 객체 생성
    if (!CurrentScene)
    {
        return false; // 월드 생성 실패
    }
    CurrentScene->Init(); // 월드 자체 초기화
    */

    // Object::Init(); 와 같은 초기화

    return true;
}

void GameManager::Update()
{
}
