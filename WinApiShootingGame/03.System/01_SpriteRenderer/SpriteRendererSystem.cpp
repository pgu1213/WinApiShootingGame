#include "../../99_Default/pch.h"
#include "../../00_MainGame/MainGame.h"

#include "../ComponentSystem.h"

#include "SpriteRendererSystem.h"
#include "../00_Transform/TransformSystem.h"

#include "../../02_Component/SpriteRenderer.h"
#include "../../02_Component/Transform.h"

SpriteRendererSystem::SpriteRendererSystem(MainGame* maingame, Entity id, HDC hdc) : m_render(new SpriteRenderer()), hdc(hdc)
{
    mainGame = maingame;
	m_id = id;
}

SpriteRendererSystem::~SpriteRendererSystem()
{
    delete m_render;
}

void SpriteRendererSystem::Update()
{
    const Transform* transform = &mainGame->GetComponent<TransformSystem>(m_id)->GetData();
    
    if (transform) {
        m_render->rect.left = transform->position.x - transform->scale.x / 2;
        m_render->rect.top = transform->position.y - transform->scale.y / 2;
        m_render->rect.right = transform->position.x + transform->scale.x / 2;
        m_render->rect.bottom = transform->position.y + transform->scale.y / 2;
        Ellipse(hdc, m_render->rect.left, m_render->rect.top, m_render->rect.right, m_render->rect.bottom);
    }


}

const SpriteRenderer& SpriteRendererSystem::GetData() const
{
    return *m_render;
}
