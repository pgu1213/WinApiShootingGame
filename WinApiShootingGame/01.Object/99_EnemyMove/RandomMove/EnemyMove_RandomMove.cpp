#include "../../../pch.h"
#include "EnemyMove_RandomMove.h"
#include "../../../00.Manager/01.GameManager/GameManager.h"

Vector2 EnemyMove_RandomMove::GetNextPosition(const Vector2& nowPos, const Vector2& nowScale)
{
	float moveScreenSizeX = GameManager::GetInstance()->GetScreenSize().x - nowScale.x / 2.f;

	float moveScreenSizeY = (GameManager::GetInstance()->GetScreenSize().y - nowScale.y / 2.f) / 2.f;
	
	float radius = 100.f;

	float left = nowPos.x - radius;
	float right = nowPos.x + radius;
	float top = nowPos.y - radius;
	float bottom = nowPos.y + radius;

	vector<pair<float, float>> angleRanges;

	if (left < 0) angleRanges.push_back({ -90.f, 90.f });
	else if (right > moveScreenSizeX) angleRanges.push_back({ 90.f, 270.f });

	if (top < 0) angleRanges.push_back({ 0.f, 180.f });
	else if (bottom > moveScreenSizeY) angleRanges.push_back({ 180.f, 360.f });

	if (angleRanges.empty()) {
		angleRanges.push_back({ 0.f, 360.f });
	}

	float minAngle = angleRanges[0].first;
	float maxAngle = angleRanges[0].second;

	for (size_t i = 1; i < angleRanges.size(); ++i) {
		minAngle = max(minAngle, angleRanges[i].first);
		maxAngle = min(maxAngle, angleRanges[i].second);
	}

	if (minAngle >= maxAngle) {
		return nowPos;
	}

	// 랜덤 각도 계산
	float angleDegree = minAngle + (static_cast<float>(rand()) / RAND_MAX) * (maxAngle - minAngle);

	float rad = angleDegree * 3.14159265f / 180.0f;

	Vector2 pos = { nowPos.x + radius * cosf(rad), nowPos.y + radius * sinf(rad) };

	float screenX = moveScreenSizeX;
	float screenY = moveScreenSizeY;

	if (pos.x < 0 || pos.x > screenX || pos.y < 0 || pos.y > screenY)
		return nowPos;
	return pos;
}
