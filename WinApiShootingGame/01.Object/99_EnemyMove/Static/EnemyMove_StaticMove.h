#pragma once
#include "../../IEnemyMove.h"

class EnemyMove_StaticMove : public IEnemyMove
{
public:
	Vector2 GetNextPosition(const Vector2& nowPos, const Vector2& nowScale) override;
};