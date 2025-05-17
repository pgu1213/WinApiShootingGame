#pragma once
#include "../04_Enemy/CEnemy.h"

class IBulletType;

class CBoss1 : public CEnemy
{
public:
	CBoss1();
	virtual ~CBoss1();
	virtual void Init(Entity id, EntityType type) override;
	virtual void Update(float DeltaTime) override;
	virtual void Release() override;
	virtual void Render(HDC hdc)override;
};

