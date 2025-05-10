#pragma once
#include "../04.Header/Vector2.h"

struct Transform {
    Vector2 position;            
    float rotation = 0.0f;      
    Vector2 scale = { 1.0f, 1.0f };  
};