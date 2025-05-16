#pragma once
#include "../01.Actor/CActor.h"

class CBullet : public CActor
{
private:
	CActor& posTarget;
public:
	CBullet(CActor& _posTarget);
	virtual ~CBullet();
	void Init(Entity id, EntityType type) override;	
	void Update(float DeltaTime) override;
	void Render(HDC hdc) override;
	void Release() override;
public:
	void SetBulletDestination(Vector2 dir, Vector2 vel, Entity targetId = NULL);
	Vector2 Normalize(Vector2 v);
};

