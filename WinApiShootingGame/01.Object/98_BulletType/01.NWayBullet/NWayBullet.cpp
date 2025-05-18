#include <cmath>
#include "NWayBullet.h"
#include "../../../00.Manager/02.SceneManager/SceneManager.h"
#include "../../../01.Object/01.Actor/CActor.h"
#include "../../../01.Object/05.Scene/CScene.h"


NWayBullet::NWayBullet(float _angle, float _bulletCount) : m_angle(_angle), m_bulletCount(_bulletCount)
{
}

void NWayBullet::Fire(CActor* shooter, float _damage, float _speed, Vector2 _dir)
{
    float radAngle = 3.14f / 180.f * m_angle;
    float rad = (m_bulletCount % 2)
        ? -(m_bulletCount / 2) * radAngle
        : -(m_bulletCount / 2 - 0.5f) * radAngle;

    for (int i = 0; i < m_bulletCount; i++, rad += radAngle)
    {
        float c = cosf(rad);
        float s = sinf(rad);

        float vecSpeedX = _dir.x * c - _dir.y * s;
        float vecSpeedY = _dir.x * s + _dir.y * c;

        Vector2 vec = Vector2{ vecSpeedX, vecSpeedY };
        SceneManager::GetInstance()->GetCurrentScene()->SpawnBullet(shooter->GetId(), _damage, _speed, vec);
    }
}
