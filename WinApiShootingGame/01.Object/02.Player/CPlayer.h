#pragma once
#include "../01.Actor/CActor.h"

class InputManager;
class IBulletType;
struct Transform;

class CPlayer : public CActor
{
private:
	InputManager* m_inputManager;
	IBulletType* bulletType;
	Vector2 m_direction;
	

	float bulletSpeed;
	int currentHP;
	int maxHP;
	float speed;
	int damage;

	bool attackAble;
public:
	CPlayer();
	virtual ~CPlayer();
	void Init(Entity id, EntityType type) override;
	void Update(float DeltaTime) override;
	void Release() override;
	void SetBulletPattern(IBulletType *pattern);
public:
	void Render(HDC hdc) override;

};

