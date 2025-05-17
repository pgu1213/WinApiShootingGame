#pragma once
#include "../04.Header/Vector2.h"
class CActor;

class IBulletType {
public:
    virtual ~IBulletType() {}
    virtual void Fire(CActor* shooter, float _damage, float _speed, Vector2 _dir) =0;
};