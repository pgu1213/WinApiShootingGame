#pragma once
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
public:
	void Init();
	void LateInit();
	void Update();
	void Render(HDC hdc);
private:
private:
	//GameScene* m_pGameScene;
	//vector<GameScene*> SceneList;
};

