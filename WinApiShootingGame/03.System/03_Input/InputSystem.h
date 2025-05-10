#pragma once
struct InputData;

class InputSystem : public ComponentSystem, public IDataProvider<InputData> {
private:
    InputManager* m_inputManager;
    InputData* m_inputData;

public:
    InputSystem(MainGame* maingame, Entity id, InputManager* inputMgr);
    virtual ~InputSystem();
    virtual void Update()override; 
    const InputData& GetData()const override;
    void ResetInput();
};