#pragma once
class MainGame;
class Transform;
class Collider;

class CollisionManager
{
private:
	MainGame* mainGame;
public:
	CollisionManager(MainGame* mainGame);
	bool CheckCollision(const Transform& aT, const Collider& aC,
		const Transform& bT, const Collider& bC);
	void ProcessCollisions();
};

