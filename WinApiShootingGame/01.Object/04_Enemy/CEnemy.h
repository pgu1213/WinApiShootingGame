#pragma once
#include "../01.Actor/CActor.h"
class CEnemy : public CActor
{
private:
	CActor* target;
public:
	virtual void Init(Entity id, EntityType type) override;
	virtual void Update(float DeltaTime) override;
	virtual void Render(HDC hdc)override;
	virtual void Release() override;	
public:
	CActor* GetTarget();
	void SetTarget(Entity id);
	Vector2 Normalize(Vector2 v);
	

};

