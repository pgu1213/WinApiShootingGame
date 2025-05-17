#pragma once
#include "../../IBulletType.h"

class NWayBullet : public IBulletType
{
private:
	float m_angle;
	int m_bulletCount;
public:
	NWayBullet(float _angle, float _bulletCount);
	void Fire(CActor* shooter, float _damage, float _speed, Vector2 _dir) override;
};

