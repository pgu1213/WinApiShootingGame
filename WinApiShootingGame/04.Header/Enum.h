#pragma once
enum class EntityType {
	Player,
	Enemy,
	PlayerBullet,
	EnemyBullet,
	UI,
	Scene,
	None,
};

enum class BulletType
{
	Single,
	NWay,
	Circle,
	None
};

enum class ColliderType {
	Box,
	Circle,
	Polygon,
	None,
};

