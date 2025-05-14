#pragma once
#include "../99.SingTonManager/SingTonManager.h"

class InputManager;
class CollisionManager;
class CObject;

using EntityTable = unordered_map<Entity, CObject*>;


class GameManager : public SingleTon<GameManager>
{
	friend class SingleTon<GameManager>;
private:
	InputManager* inputManager;
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
	Vector2 GetScreenSize();
	void RemoveEntity(Entity id);
	Vector2 Normalize(Vector2 v);

	void SpawnBullet(Entity shooterId);
	void SpawnBullet(Entity shooterId, Vector2 pos, Vector2 velocity);
	
	const EntityTable* GetEntityTable() const;
	
	void AddEntityTable(Entity id, CObject* obj);
};

