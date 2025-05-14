#include "../../pch.h"
#include "CPlayer.h"
#include "../../03.System/ComponentSystem.h"
#include "../../03.System/00_Transform/TransformSystem.h"
#include "../../03.System/01_SpriteRenderer/SpriteRendererSystem.h""
#include "../../03.System/04_Rigid/RigidbodySystem.h"
#include "../../03.System/03_Input/InputSystem.h"
#include "../../03.System/02_Collider/ColliderSystem.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init(Entity id, EntityType type, ComponentTable compTable)
{
	CObject::Init(id, type, compTable);
}

void CPlayer::Update(float DeltaTime)
{
	CObject::Update(DeltaTime);
}

void CPlayer::Render(HDC hdc)
{
}

void CPlayer::Release()
{
}
