#pragma once
#include "../99.SingTonManager/SingTonManager.h"

class ComponentSystem;
class InputManager;
class CollisionManager;
class CObject;

using ComponentTable = map<type_index, ComponentSystem*>;
using ObjectTable = unordered_map<Entity, ComponentTable>;
using EntityTable = unordered_map<Entity, CObject*>;


class GameManager : public SingleTon<GameManager>
{
	friend class SingleTon<GameManager>;
private:
	InputManager* inputManager;
	CollisionManager* collisionManager;

	ObjectTable m_gameObjectTable;
	EntityTable m_entityTable;
	vector<Entity> removeEntityQueue;
	
	HDC hdc;

	int currentEntityID = 0;
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
public:
	Entity CreateEntity();
	Vector2 GetScreenSize();
	void RemoveEntity(Entity id);
	Vector2 Normalize(Vector2 v);
	void SpawnBullet(Entity shooterId);
	void SpawnBullet(Entity shooterId, Vector2 pos, Vector2 velocity);
	
	const ObjectTable* GetObjectTable() const;
	const EntityTable* GetEntityTable() const;
	
	void AddEntityTable(Entity id);

	template <typename T>
	const T* GetComponent(Entity id)
	{
		auto entityIt = m_gameObjectTable.find(id);
		if (entityIt != m_gameObjectTable.end()) {
			const ComponentTable& table = entityIt->second;
			auto compIt = table.find(typeid(T));
			if (compIt != table.end()) {
				return dynamic_cast<T*>(compIt->second);
			}
		}
		return nullptr;
	}
private:
	//GameScene* m_pGameScene;
	//vector<GameScene*> SceneList;
};

