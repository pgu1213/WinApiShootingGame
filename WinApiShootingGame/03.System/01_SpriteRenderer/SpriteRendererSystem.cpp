#include "../../pch.h"
#include "../../00.Manager/06.ResourceManager/ResourceManager.h"
#include "../ComponentSystem.h"
#include "SpriteRendererSystem.h"
#include "../00_Transform/TransformSystem.h"
#include "../../02.Component/SpriteRenderer.h"
#include "../../02.Component/Transform.h"

SpriteRendererSystem::SpriteRendererSystem(CActor* owner, HDC hdc) : m_render(new SpriteRenderer()), hdc(hdc)
{
	m_owner = owner;
	
}

SpriteRendererSystem::~SpriteRendererSystem()
{
	delete m_render;
}

void SpriteRendererSystem::Init()
{
	// 이 컴포넌트의 기본 이미지 설정 (유니티로 따지면 캡슐 스프라이트를 바로 생성시키는 느낌?)
}

void SpriteRendererSystem::Update(float _deltaTime)
{
	// 애니메이션이 들어가면 추가 예정
}

void SpriteRendererSystem::Render(HDC hdc)
{
	// 오브젝트의 Transform 컴포넌트를 가져옴
	const Transform& m_transform = m_owner->GetComponent<TransformSystem>()->GetData();

	// 스프라이트 렌더러의 데이터 가져옴
	const SpriteRenderer& spriteData = GetData();

	// 스프라이트 렌더러의 이미지 파일 경로를 통해 이미지를 가져옴
	Gdiplus::Bitmap* bitmap = ResourceManager::GetInstance()->GetSprite(spriteData.filePath);

	if (!bitmap)
	{
		return;
	}

	Gdiplus::Graphics graphics(hdc);
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

	// 스프라이트의 최종 위치 및 크기 계산 (Transform 적용)
	int spriteWidth = static_cast<int>(m_transform.scale.x);
	int spriteHeight = static_cast<int>(m_transform.scale.y);
	int spriteLeft = static_cast<int>(m_transform.position.x - spriteWidth / 2); // 가운데 기준
	int spriteTop = static_cast<int>(m_transform.position.y - spriteHeight / 2); // 가운데 기준

	Gdiplus::Status drawStatus = graphics.DrawImage(bitmap, spriteLeft, spriteTop, spriteWidth, spriteHeight);
}

const SpriteRenderer& SpriteRendererSystem::GetData() const
{
	return *m_render;
}

SpriteRenderer& SpriteRendererSystem::GetModifyData()
{
	return *m_render;
}
