#pragma once
#include "../01.Actor/CActor.h"

class CBullet : public CActor
{
private:
	CActor& m_shooter;
	float m_damage;
	float m_speed;
public:
	CBullet(CActor& _posTarget, float _damage, float _speed);
	virtual ~CBullet();
	void Init(Entity id, EntityType type) override;
	void Update(float DeltaTime) override;
	void Release() override;
public:
	void SetBulletDirection(Vector2 _dir);
	float GetDamage();
public:
	void Render(HDC hdc) override;
};

