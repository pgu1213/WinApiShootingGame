#pragma
#include "../99.SingTonManager/SingTonManager.h"

class SceneManager : public SingleTon<SceneManager>
{
friend class SingleTon<SceneManager>;
private:
	explicit SceneManager();
public:
	virtual ~SceneManager();
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	// 씬을 추가하는 함수
	// 씬 이름과 씬 객체를 매개변수로 받아서 SceneList에 추가
	// 씬에 object을 추가하는 함수
private:
	CObject* m_pCurrentScene;
	CObject* m_pNextScene;
	map<string, CObject*> SceneList;
};

