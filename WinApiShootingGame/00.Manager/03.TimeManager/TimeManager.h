#pragma once
#include "../99.SingTonManager/SingTonManager.h"

class TimeManager : public SingleTon<TimeManager>
{
friend class SingleTon<TimeManager>;
private:
    explicit TimeManager();
public:
    virtual ~TimeManager();
public:
    static bool Init(); // TimeManager 초기화 함수
    static void Update(); // 매 프레임 호출하여 델타 시간을 업데이트하는 함수
    static float GetDeltaTime(); // 현재 프레임의 델타 시간(초)을 반환하는 함수
    static float GetTotalTime(); // 프로그램 시작 후 총 경과 시간(초)을 반환하는 함수
    static double GetTotalElapsedTimeDouble(); // 필요에 따라 총 경과 시간을 double로 반환하는 함수를 추가할 수 있습니다.

private:
    static LARGE_INTEGER PreviousCounter; // 이전 프레임의 카운터
    static LARGE_INTEGER Frequency; // 고성능 카운터의 주파수
    static float CurrentDeltaTime; // 현재 프레임의 델타 시간
    static double TotalElapsedTime; // 총 경과 시간
};

