#pragma once
#include <cmath>
#include "Vector2.h"

inline Vector2 Normalize(Vector2 v)
{
    float len = sqrtf(v.x * v.x + v.y * v.y);
    return Vector2{ v.x / len, v.y / len };
}

inline float GetDistance(Vector2 a, Vector2 b)
{
    return sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

inline Vector2 DistanceNormalize(Vector2 a, Vector2 b)
{
    Vector2 dir = { b.x - a.x, b.y - a.y };
    float length = GetDistance(a,  b);
    if (length != 0.f)
        return { dir.x / length, dir.y / length };
    else
        return { 0.f, 0.f };
}