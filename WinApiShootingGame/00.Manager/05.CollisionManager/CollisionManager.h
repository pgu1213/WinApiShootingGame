#pragma once
class GameManager;
class Transform;
class Collider;

class CollisionManager
{
private:
	GameManager* gameManager;
public:
	CollisionManager(GameManager* gameMgr);
	bool CheckCollision(const Transform& aT, const Collider& aC,
		const Transform& bT, const Collider& bC);
	void ProcessCollisions();
};

