#pragma once
#include "../04.Header/Vector2.h"
#include <vector>

struct Collider {
    ColliderType colType = ColliderType::None; 
    Vector2 offset = { 0.f, 0.f };
    Vector2 size = { 50.f, 50.f };     
    float radiusX = 0.f;              
    float radiusY = 0.f;               

};