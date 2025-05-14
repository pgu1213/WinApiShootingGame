#pragma once
#include "../00.Default/CObject.h"

class InputManager;

class CPlayer : public CObject
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

