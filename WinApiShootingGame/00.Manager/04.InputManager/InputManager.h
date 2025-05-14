#pragma once

class InputManager 
{
public:
    void BindActionKey(int keyCode, const string& actionName);
    void BindAxisKey(int negative_keyCode, int Positive_keyCode, const string& axisName);    
    const unordered_map<string, int>& GetKeyBindings() const;

    int GetAxis(const string& axisName) const;
    bool GetKey(const string& keyName) const;

private:
    unordered_map<string, int> m_keyBindings;
    unordered_map<string, pair<int, int>> m_axisKeyBindings;
};