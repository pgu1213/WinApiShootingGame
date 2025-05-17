#include <cmath>
#include "CircleBullet.h"
#include "../../../00.Manager/02.SceneManager/SceneManager.h"
#include "../../../01.Object/01.Actor/CActor.h"
#include "../../../01.Object/05.Scene/CScene.h"

CircleBullet::CircleBullet(int _bulletCount) : m_bulletCount(_bulletCount)
{
}

void CircleBullet::Fire(CActor* shooter, float _damage, float _speed, Vector2 _dir)
{
	float radAngle = 3.14f * 2 / m_bulletCount;
	float rad = m_bulletCount % 2 != 0 ? radAngle / 2 : 0;

    for (int i = 0; i < m_bulletCount; i++, rad += radAngle)
    {
        float c = cosf(rad);
        float s = sinf(rad);

        Vector2 dir = { c, s };
      
        SceneManager::GetInstance()->GetCurrentScene()->SpawnBullet(shooter->GetId(), _damage, _speed, dir);
    }
}
