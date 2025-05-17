#pragma once
#include "../01.Actor/CActor.h"

class CBullet : public CActor
{
private:
	CActor& m_shooter;
	float m_damage;
public:
	CBullet(CActor& _posTarget, float _damage);
	virtual ~CBullet();
	void Init(Entity id, EntityType type) override;
	void Update(float DeltaTime) override;
	void Release() override;
public:
	void SetBulletDestination(CActor* target);
	float GetDamage();
public:
	void Render(HDC hdc) override;
};

