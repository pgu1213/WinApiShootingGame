#pragma once
#include "../99.SingTonManager/SingTonManager.h"

class CollisionManager;
class CActor;

using EntityTable = unordered_map<Entity, CActor*>;

class GameManager : public SingleTon<GameManager>
{
	friend class SingleTon<GameManager>;
private:
	CollisionManager* collisionManager;

	Entity playerId;
	Entity currentEntityID;
	HDC hdc;

private:
	explicit GameManager();
public:
	virtual ~GameManager();
public:
	bool Init();
	void Update(float DeltaTime);
	void Render(HDC hdc);
public:
	static Vector2 GetScreenSize();
	Entity CreateEntity();
private:
	void CheckStageClear();
};

