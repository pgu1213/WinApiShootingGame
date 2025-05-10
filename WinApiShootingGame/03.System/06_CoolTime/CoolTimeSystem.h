#pragma once
struct CoolTime;

class CoolTimeSystem : public ComponentSystem, public IDataProvider<CoolTime>
{
private:
	float  m_lastUpdateTime;
	CoolTime* m_coolTime;
	bool isActive;			// 쿨타임인지 체크
public:
	CoolTimeSystem(CObject* owner, CoolTime* coolTime);
	virtual ~CoolTimeSystem();
	void StartCooldown();
	bool CheckActive();
	void Update(float _deltaTime) override;
	const CoolTime& GetData() const override;

};

