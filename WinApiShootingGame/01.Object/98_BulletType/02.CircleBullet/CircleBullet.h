#pragma once
#include "../../IBulletType.h"
class CircleBullet : public IBulletType
{
private:
	int m_bulletCount;
public:
	CircleBullet(int _bulletCount);
	void Fire(CActor* shooter, float _damage, float _speed, Vector2 _dir) override;
};

