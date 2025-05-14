#pragma once
#include "../01.Actor/CActor.h"

class InputManager;

class CPlayer : public CActor
{
private:
	InputManager* inputManager;
public:
	CPlayer();
	virtual ~CPlayer();
	void Init(Entity id, EntityType type) override;
	void Update(float DeltaTime) override;
	void Render(HDC hdc) override;
	void Release() override;
};

