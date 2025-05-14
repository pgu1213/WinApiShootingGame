#pragma once
#include "../00.Default/CObject.h"

class CPlayer : public CObject
{
private:

public:
	CPlayer();
	virtual ~CPlayer();
	void Init(Entity id, EntityType type, ComponentTable compTable) override;
	void Update(float DeltaTime) override;
	void Render(HDC hdc) override;
	void Release() override;
};

