#pragma once
#include "../01.Actor/CActor.h"

class IEnemyMove;

class CEnemy : public CActor
{
private:
	IEnemyMove* moveLogic;

	Vector2 enterTargetPos; 
	Vector2 moveDestination;
	CActor* target;
	int currentHP;
	int maxHP;
	float speed;
	int damage;
	bool isEnteringScreen;
	bool isMoveAble;
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
	void Render(HDC hdc)override;

	Vector2 SpawnOutScreen();
	Vector2 GetMoveTward(Vector2 current, Vector2 target);
};

