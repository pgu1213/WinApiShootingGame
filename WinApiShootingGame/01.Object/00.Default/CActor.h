#pragma once
#include "CObject.h"

class CActor : public CObject
{
public:
    CActor(const string& Name = "Actor");
	virtual ~CActor();
public:
	virtual void Init() override;
	virtual void Update(float DeltaSeconds) override;
	virtual void Release() override;
	// TODO -  컴포넌트 추가
};

