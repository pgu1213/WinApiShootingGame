#pragma once
#include "../../IBulletType.h"

class SingleBullet : public IBulletType
{
public:
	void Fire(CActor* shooter, float _damage, float _speed, Vector2 _dir) override;

};

