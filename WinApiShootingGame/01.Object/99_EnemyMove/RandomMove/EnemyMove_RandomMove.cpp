#include "../../../pch.h"
#include "EnemyMove_RandomMove.h"
#include "../../../00.Manager/01.GameManager/GameManager.h"

EnemyMove_RandomMove::EnemyMove_RandomMove(float _radius, float _minX , float _maxX , float _minY , float _maxY) : radius(_radius), minX(_minX), maxX(_maxX),
minY(_minY), maxY(_maxY)
{
}

Vector2 EnemyMove_RandomMove::GetNextPosition(const Vector2& nowPos, const Vector2& nowScale)
{
	Vector2 screenSize = GameManager::GetInstance()->GetScreenSize();

	float moveMinX = nowScale.x / 2.f + minX;
	float moveMaxX = screenSize.x - nowScale.x / 2.f - maxX;
	float moveMinY = nowScale.y / 2.f + minY;
	float moveMaxY = (screenSize.y - nowScale.y / 2.f) / 2.f - maxY;

	// 동적 반경 계산
	float screenCenterX = screenSize.x / 2.f;
	float distFromCenter = fabs(nowPos.x - screenCenterX);
	
	float minRadius = radius / 2.f;
	float maxRadius = radius * 2.f;

	float dynamicRadius = minRadius + (distFromCenter / screenCenterX) * (maxRadius - minRadius);
	dynamicRadius = clamp(dynamicRadius, minRadius, maxRadius);

	float minAngle = 0.f;
	float maxAngle = 360.f;

	// 이동 각도 설정
	if (nowPos.x - dynamicRadius < moveMinX) {		//왼쪽
		minAngle = -90.f;
		maxAngle = 90.f;
	}
	else if (nowPos.x + dynamicRadius > moveMaxX) {	// 오른쪽
		minAngle = 90.f;
		maxAngle = 270.f;
	}

	if (nowPos.y - dynamicRadius < moveMinY) {		// 위쪽
		minAngle = max(minAngle, 0.f);
		maxAngle = min(maxAngle, 180.f);
	}
	else if (nowPos.y + dynamicRadius > moveMaxY) {	// 아래쪽
		minAngle = max(minAngle, 180.f);
		maxAngle = min(maxAngle, 360.f);
	}
	


	// 랜덤 각도 계산 및 위치 리턴
	float randFloat = static_cast<float>(rand()) / RAND_MAX;
	
	float angleDegree = minAngle + randFloat * (maxAngle - minAngle);

	float rad = angleDegree * 3.14f / 180.f;

	Vector2 pos = { nowPos.x + dynamicRadius * cosf(rad), nowPos.y + dynamicRadius * sinf(rad) };

	if (pos.x < moveMinX || pos.x > moveMaxX || pos.y < moveMinY || pos.y > moveMaxY) {		
		pos.x = clamp(pos.x, moveMinX, moveMaxX);
		pos.y = clamp(pos.y, moveMinY, moveMaxY);
	}

	return pos;
}




