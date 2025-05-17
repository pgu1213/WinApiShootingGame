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
	bool CheckBoxCollision(const Transform& aT, const Collider& aC,
		const Transform& bT, const Collider& bC);
	bool CheckCircleCollision(const Transform& ta, const Collider& ca, const Transform& tb, const Collider& cb);
	void ProcessCollisions();
};

