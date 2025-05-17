#pragma once
#include "../../IEnemyMove.h"
class EnemyMove_FixedPathMove:public IEnemyMove
{
private:
	vector<Vector2> path;
	int index = 0;
public:
	EnemyMove_FixedPathMove();
	Vector2 GetNextPosition(const Vector2& nowPos, const Vector2& nowScale) override;
};