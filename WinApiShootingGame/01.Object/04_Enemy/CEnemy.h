#pragma once
#include "../01.Actor/CActor.h"

class IEnemyMove;
class IBulletType;

class CEnemy : public CActor
{
protected:
	IEnemyMove* moveLogic;
	vector<IBulletType*> bulletType;

	Vector2 moveDestination;
	float m_bulletSpeed;
	CActor* target;

	int currentHP;
	int maxHP;
	float speed;
	int damage;
	bool isEnteringScreen;
	bool isMoveAble;

protected:
	Vector2 SpawnOutScreen(Vector2 _scale);
	Vector2 GetMoveTward(Vector2 current, Vector2 target);

public:
	CEnemy();
	virtual ~CEnemy();
	virtual void Init(Entity id, EntityType type) override;
	virtual void Update(float DeltaTime) override;
	virtual void Release() override;

public:
	CActor* GetTarget();
	void SetTarget(Entity id);

public:
	virtual void Render(HDC hdc)override;
};

