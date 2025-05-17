#pragma once
#include "../../IEnemyMove.h"

class EnemyMove_RandomMove : public IEnemyMove
{
private:
    int movePrecision = 1000;
public:
    Vector2 GetNextPosition(const Vector2& nowPos, const Vector2& nowScale) override;
};

