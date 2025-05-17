#include "SingleBullet.h"
#include "../../../00.Manager/02.SceneManager/SceneManager.h"
#include "../../../01.Object/01.Actor/CActor.h"
#include "../../../01.Object/05.Scene/CScene.h"

void SingleBullet::Fire(CActor* shooter, float _damage, float _speed, Vector2 _dir)
{
	SceneManager::GetInstance()->GetCurrentScene()->SpawnBullet(shooter->GetId(), _damage, _speed, _dir);
}

