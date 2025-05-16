#pragma once
struct CoolTime;

class CoolTimeSystem : public ComponentSystem, public IDataProvider<CoolTime>
{
private:
	float  m_lastUpdateTime;
	CoolTime* m_coolTime;
	bool isActive;			// 쿨타임인지 체크
public:
	CoolTimeSystem(CActor* owner, CoolTime* coolTime);
	virtual ~CoolTimeSystem();
	virtual void Init() override;
	void StartCooldown();
	bool CheckActive();
	void Update(float _deltaTime) override;
	 CoolTime& GetData() const override;

};

