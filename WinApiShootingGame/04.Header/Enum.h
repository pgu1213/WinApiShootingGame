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

enum class EnemyMoveType
{
	RandomCircle,
	FixedPath,
	Static,
};