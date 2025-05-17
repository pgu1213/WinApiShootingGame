#include "SingleBullet.h"
#include "../../../00.Manager/01.GameManager/GameManager.h"
#include "../../../01.Object/01.Actor/CActor.h"

void SingleBullet::Fire(CActor* shooter, float _damage, float _speed, Vector2 _dir)
{
	GameManager::GetInstance()->SpawnBullet(shooter->GetId(), _damage, _speed, _dir);
}

