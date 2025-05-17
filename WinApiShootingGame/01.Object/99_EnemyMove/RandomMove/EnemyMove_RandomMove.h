#pragma once
#include "../../IEnemyMove.h"
#include "../../../04.Header/Vector2.h"

class EnemyMove_RandomMove : public IEnemyMove
{
private:
	float radius;
	
	float minX;
	float maxX;
	float minY;
	float maxY;	
public:
	EnemyMove_RandomMove(float _radius, float _minX = 0.f, float _maxX = 0.f, float _minY = 0.f, float _maxY = 0.f);
	Vector2 GetNextPosition(const Vector2& nowPos, const Vector2& nowScale) override;
};

