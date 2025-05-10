#pragma once
class MainManager
{
public:
	MainManager();
	~MainManager();
public:
	void Init();
	void LateInit();
	void Update();
	void Render(HDC hdc);
};

