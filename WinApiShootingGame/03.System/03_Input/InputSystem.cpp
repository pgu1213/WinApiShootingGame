#include "../../pch.h"
#include "../../00.Manager/04.InputManager/InputManager.h"
#include "../ComponentSystem.h"
#include "InputSystem.h"
#include "../../02.Component/InputData.h"

InputSystem::InputSystem(MainGame* maingame, Entity id, InputManager* inputMgr) : m_inputManager(inputMgr), m_inputData(new InputData)
{
    mainGame = maingame;
    m_id = id;
}

InputSystem::~InputSystem()
{
    delete m_inputData;
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

void InputSystem::Update()
{
    //ResetInput();
    m_inputData->horizontal = m_inputManager->GetAxis("Horizontal");
    m_inputData->vertical = m_inputManager->GetAxis("Vertical");

    if (m_inputManager->GetKey("Shoot")) {
        mainGame->SpawnBullet(m_id);
    }
}

