#pragma once
#include "../99.SingTonManager/SingTonManager.h"

class GameManager : public SingleTon<GameManager>
{
	friend class SingleTon<GameManager>;
private:
	explicit GameManager();
public:
	virtual ~GameManager();
public:
	bool Init();
	void Update(float DeltaTime);
private:
	//GameScene* m_pGameScene;
	//vector<GameScene*> SceneList;
};

