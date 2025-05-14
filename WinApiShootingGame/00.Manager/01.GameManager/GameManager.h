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

	EntityTable m_entityTable;
	vector<Entity> removeEntityQueue;

	Entity playerId;
	HDC hdc;

	Entity currentEntityID;
private:
	void GeneratePlayer();
	void GenerateEnemy();
private:
	explicit GameManager();
public:
	virtual ~GameManager();	
public:
	bool Init();
	void Update(float DeltaTime);
	void Render(HDC hdc);
public:
	Entity CreateEntity();
	void RemoveEntity(Entity id);

	Vector2 Normalize(Vector2 v);

	void SpawnBullet(Entity shooterId);
	void SpawnBullet(Entity shooterId, Vector2 pos, Vector2 velocity);
	
	static Vector2 GetScreenSize();
	const EntityTable* GetEntityTable()const;
	
	void AddEntityTable(Entity id, CActor* obj);
};

