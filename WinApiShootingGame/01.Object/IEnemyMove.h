#pragma once
#include "../04.Header/Vector2.h"

class IEnemyMove
{
public:
    virtual ~IEnemyMove() = default;
    virtual Vector2 GetNextPosition(const Vector2& nowPos, const Vector2& nowScale) = 0;
};