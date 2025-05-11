#include "../../pch.h"
#include "../../00.Manager/01.GameManager/GameManager.h"
#include "../../00.Manager/04.InputManager/InputManager.h"
#include "../ComponentSystem.h"
#include "InputSystem.h"
#include "../../02.Component/InputData.h"

InputSystem::InputSystem(CObject* owner, GameManager* gameMgr, InputManager* inputMgr) : m_inputManager(inputMgr), m_gameManager(gameMgr), m_inputData(new InputData)
{
    m_owner = owner;
}

InputSystem::~InputSystem()
{
    delete m_inputData;
}

void InputSystem::Init()
{
}

const InputData& InputSystem::GetData() const
{
    return *m_inputData;
}

void InputSystem::ResetInput()
{
    m_inputData->horizontal = 0;
    m_inputData->vertical = 0;
    m_inputData->space = false;
}

void InputSystem::Update(float _deltaTime)
{
    //ResetInput();
    m_inputData->horizontal = m_inputManager->GetAxis("Horizontal");
    m_inputData->vertical = m_inputManager->GetAxis("Vertical");

    if (m_inputManager->GetKey("Shoot")) {
        m_gameManager->SpawnBullet(m_owner->GetId());
    }
}

void InputSystem::Render(HDC hdc)
{
}

