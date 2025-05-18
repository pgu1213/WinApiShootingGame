#pragma once

struct Timer
{
	float currentTime = 0.0f;
	float coolTime = 0.0f;
	bool isActive = false;
	std::function<void()> onActiveEvent = nullptr;
};

class CoolTimeSystem : public ComponentSystem
{
private:
    unordered_map<string, Timer> timerMap; 
public:
    CoolTimeSystem(CActor* owner);
    virtual ~CoolTimeSystem();

    void Init() override;

    // 키에 쿨타임 추가
    void AddTimer(const std::string& key, float coolTime, std::function<void()> onComplete = nullptr);

    // 키에 해당하는 쿨타임 시작
    void StartCooldown(const std::string& key);

    // 매 프레임 갱신
    void Update(float deltaTime) override;

};

