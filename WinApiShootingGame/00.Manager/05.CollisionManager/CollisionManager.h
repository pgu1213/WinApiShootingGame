#pragma once
class SceneManager;
class Transform;
class Collider;

class CollisionManager
{
private:
	SceneManager* sceneManager;
public:
	CollisionManager(SceneManager* sceneMgr);
	bool CheckBoxCollision(const Transform& aT, const Collider& aC,
		const Transform& bT, const Collider& bC);
	bool CheckCircleCollision(const Transform& ta, const Collider& ca, const Transform& tb, const Collider& cb);
	void ProcessCollisions();
};

