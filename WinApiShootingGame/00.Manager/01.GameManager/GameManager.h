#pragma once
#include "../99.SingTonManager/SingTonManager.h"

class CollisionManager;
class CActor;

using EntityTable = unordered_map<Entity, CActor*>;

class GameManager : public SingleTon<GameManager>
{
	friend class SingleTon<GameManager>;
private:
	EntityTable m_entityTable;
	vector<Entity> removeEntityVec;

	CollisionManager* collisionManager;

	Entity playerId;
	Entity currentEntityID;
	HDC hdc;

private:
	Entity CreateEntity();
	void GeneratePlayer();
	void GenerateEnemy();	

	void AddEntityTable(Entity id, CActor* obj);
	void RemoveEntity(Entity id);

private:
	explicit GameManager();
public:
	virtual ~GameManager();	
public:
	bool Init();
	void Update(float DeltaTime);
	void Render(HDC hdc);
public:
	Vector2 Normalize(Vector2 v);	
	static Vector2 GetScreenSize();
	const EntityTable* GetEntityTable();
	void AddRemoveVector(Entity id);

	void SpawnBullet(Entity shooterId);
	void SpawnBullet(Entity shooterId, Vector2 pos, Vector2 velocity);
};

