#pragma once
#include "99.SingTonManager/SingTonManager.h"

class MainManager : public SingleTon<MainManager>
{
	friend class SingleTon<MainManager>;
private:
	explicit MainManager();
public:
	virtual ~MainManager();
public:
	void Init();
	void LateInit();
	void Update();
	void Render(HDC hdc);
};

