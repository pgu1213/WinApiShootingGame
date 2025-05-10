#pragma once
#include "Object.h"

class Actor : public Object
{
public:
    Actor(const string& Name = "Actor");
	virtual ~Actor();
public:
	virtual void Init() override;
	virtual void Update(float DeltaSeconds) override;
	virtual void Release() override;
	// TODO -  컴포넌트 추가
};

