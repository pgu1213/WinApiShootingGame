#pragma once
#include "../01.Actor/CActor.h"
class CEnemy : public CActor
{
public:
	virtual void Init(Entity id, EntityType type) override;
	virtual void Update(float DeltaTime) override;
	virtual void Render(HDC hdc)override;
	virtual void Release() override;

};

