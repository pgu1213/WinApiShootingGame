#include "../../../pch.h"
#include "EnemyMove_FixedPathMove.h"

EnemyMove_FixedPathMove::EnemyMove_FixedPathMove()
{
    // 초기 경로값
    path.push_back({ 300, 200 });
    path.push_back({ 400, 250 });
    path.push_back({ 500, 300 });
}

Vector2 EnemyMove_FixedPathMove::GetNextPosition(const Vector2& nowPos, const Vector2& nowScale)
{
    if (path.empty() || index + 1 == path.size())
        return nowPos;
    index = (index + 1) % path.size();
    return path[index];
}
