#pragma
#include "../99.SingTonManager/SingTonManager.h"

class CScene;

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
	void Update(float DeltaTime);
	void Render(HDC hdc);
public:
	void AddScene(CScene* Scene);
	bool ChangeScene(const std::string& sceneName);
	CScene* GetCurrentScene() const;
	void ReleaseCurrentScene();
private:
	CScene* m_pCurrentScene;
	map<string, CScene*> m_SceneList;
};

