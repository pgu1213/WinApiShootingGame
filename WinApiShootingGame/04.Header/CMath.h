#pragma once
#include <cmath>
#include "Vector2.h"

inline Vector2 Normalize(Vector2 v)
{
    float len = sqrtf(v.x * v.x + v.y * v.y);
    return (len != 0) ? Vector2{ v.x / len, v.y / len } : Vector2{ 0.f, 0.f };
}

inline float GetDistance(Vector2 a, Vector2 b)
{
    return sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}