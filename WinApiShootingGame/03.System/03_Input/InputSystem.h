#pragma once
struct InputData;

class InputSystem : public ComponentSystem, public IDataProvider<InputData> {
private:
    GameManager* m_gameManager;
    InputManager* m_inputManager;
    InputData* m_inputData;

public:
    InputSystem(CObject* owner,GameManager* m_gameManager, InputManager* inputMgr);
    virtual ~InputSystem();
    virtual void Init() override;
    virtual void Update(float _deltaTime)override;
	virtual void Render(HDC hdc) override;
    const InputData& GetData()const override;
    void ResetInput();
};