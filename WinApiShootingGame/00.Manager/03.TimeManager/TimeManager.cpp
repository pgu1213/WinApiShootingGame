#include "../../pch.h"
#include "TimeManager.h"

LARGE_INTEGER TimeManager::PreviousCounter = { 0 };
LARGE_INTEGER TimeManager::Frequency = { 0 };
float TimeManager::CurrentDeltaTime = 0.0f;
double TimeManager::TotalElapsedTime = 0.0;

bool TimeManager::Init()
{
    // 고성능 카운터의 주파수를 가져와서 사용 가능한지 체크
    if (!QueryPerformanceFrequency(&Frequency))
    {
               return false;
    }

    // 첫 프레임의 시작 카운터 값
    QueryPerformanceCounter(&PreviousCounter);

    // 초기화
    CurrentDeltaTime = 0.0f;
    TotalElapsedTime = 0.0;

    return true;
}

// DeltaTime 업데이트
void TimeManager::Update()
{
    LARGE_INTEGER CurrentCounter; // 현재 프레임의 카운터 값
    QueryPerformanceCounter(&CurrentCounter); // 현재 카운터 값

    LONGLONG DeltaCounter = CurrentCounter.QuadPart - PreviousCounter.QuadPart; // 이전 카운터 값과 현재 카운터 값 차이

    CurrentDeltaTime = static_cast<float>((double)DeltaCounter / Frequency.QuadPart); // 델타 카운터 값을 주파수로 나누어 델타 시간 변환
    TotalElapsedTime += CurrentDeltaTime;     // 총 경과 시간에 현재 델타 시간 추가
    PreviousCounter = CurrentCounter; // 다음 프레임을 계산을 위해 현재 카운터 값을 이전 카운터 값으로 저장하기
}

float TimeManager::GetDeltaTime()
{
    return CurrentDeltaTime;
}

float TimeManager::GetTotalTime()
{
    // 혹시나 float 필요할까봐
    return static_cast<float>(TotalElapsedTime);
}

double TimeManager::GetTotalElapsedTimeDouble()
{
    return TotalElapsedTime;
}
