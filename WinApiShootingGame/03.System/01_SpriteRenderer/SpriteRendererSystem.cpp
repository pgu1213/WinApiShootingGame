#include "../../pch.h"
#include "../ComponentSystem.h"
#include "SpriteRendererSystem.h"
#include "../00_Transform/TransformSystem.h"
#include "../../02.Component/SpriteRenderer.h"
#include "../../02.Component/Transform.h"

SpriteRendererSystem::SpriteRendererSystem(MainGame* maingame, Entity id, HDC hdc) : m_render(new SpriteRenderer()), hdc(hdc)
{
	mainGame = maingame;
	m_id = id;
	m_transform = mainGame->GetComponent<TransformSystem>(m_id)->GetData();
}

SpriteRendererSystem::~SpriteRendererSystem()
{
	delete m_render;
}

void SpriteRendererSystem::Update()
{
	m_render->rect.left = m_transform.position.x - m_transform.scale.x / 2;
	m_render->rect.top = m_transform.position.y - m_transform.scale.y / 2;
	m_render->rect.right = m_transform.position.x + m_transform.scale.x / 2;
	m_render->rect.bottom = m_transform.position.y + m_transform.scale.y / 2;
	Ellipse(hdc, m_render->rect.left, m_render->rect.top, m_render->rect.right, m_render->rect.bottom);
}

const SpriteRenderer& SpriteRendererSystem::GetData() const
{
	return *m_render;
}
