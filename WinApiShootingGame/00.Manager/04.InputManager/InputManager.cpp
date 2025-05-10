#include "../../99_Default/pch.h"
#include "../../02_Component/InputData.h"
#include "InputManager.h"

void InputManager::BindActionKey(int keyCode, const string& actionName)
{
    m_keyBindings[actionName] = keyCode;
}

void InputManager::BindAxisKey(int negative_keyCode, int Positive_keyCode, const string& axisName)
{
    m_axisKeyBindings[axisName] = { negative_keyCode, Positive_keyCode };
}

const unordered_map<string, int>& InputManager::GetKeyBindings() const
{
    return m_keyBindings;
}

int InputManager::GetAxis(const std::string& axisName) const {
    int value = 0;

    auto it = m_axisKeyBindings.find(axisName);
    if (it != m_axisKeyBindings.end()) {
        int negativeKey = it->second.first;
        int positiveKey = it->second.second;

        if (GetAsyncKeyState(negativeKey) & 0x8000) value -= 1;
        else if (GetAsyncKeyState(positiveKey) & 0x8000) value += 1;
    }

    return value;
}

bool InputManager::GetKey(const string& keyName) const {
    auto it = m_keyBindings.find(keyName);
    if (it != m_keyBindings.end()) {
        return (GetAsyncKeyState(it->second) & 0x0001);
    }
    return false;
}
