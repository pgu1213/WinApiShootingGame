#include "../../pch.h"
#include "SceneManager.h"
#include "../01.GameManager/GameManager.h"
#include "../../01.Object/05.Scene/CScene.h"

#include "../../01.Object/05.Scene/01.Stage/Stage1.h"
#include "../../01.Object/05.Scene/01.Stage/Stage2.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
    AddScene(new Stage1());
    AddScene(new Stage2());

    ChangeScene("Stage1");
}

void SceneManager::Release()
{
    for (auto& scene : m_SceneList)
    {
        delete scene.second;
    }
    m_SceneList.clear();
    if (m_pCurrentScene)
    {
        m_pCurrentScene->Release();
        delete m_pCurrentScene;
        m_pCurrentScene = nullptr;
    }
}

void SceneManager::Update(float DeltaTime)
{
    if (m_pCurrentScene)
    {
        m_pCurrentScene->Update(DeltaTime);
    }
}

void SceneManager::Render(HDC hdc)
{
    if (m_pCurrentScene)
    {
        m_pCurrentScene->Render(hdc);
    }
}

void SceneManager::AddScene(CScene* Scene)
{
    if (Scene)
    {
        m_SceneList[Scene->GetSceneName()] = Scene;
    }
}

bool SceneManager::ChangeScene(const std::string& sceneName)
{
    auto it = m_SceneList.find(sceneName);
    if (it == m_SceneList.end())
    {
        MessageBoxA(NULL, ("Scene을 찾을 수 없음" + sceneName).c_str(), "실패", MB_ICONERROR | MB_OK);
        return false;
    }

    CScene* NextScene = it->second;

    // 현재 활성화된 씬이 있으면 Release 호출
    if (m_pCurrentScene)
    {
        m_pCurrentScene->Release();
    }

    m_pCurrentScene = NextScene;

    // 새로운 씬 초기화
    if (m_pCurrentScene)
    {
        Entity SceneId = GameManager::GetInstance()->CreateEntity();

        m_pCurrentScene->Init(SceneId, EntityType::Scene);

        return true;
    }

    return false;
}

void SceneManager::ReleaseCurrentScene()
{
    if (m_pCurrentScene)
    {
        delete m_pCurrentScene;
        m_pCurrentScene = nullptr;
    }
}

CScene* SceneManager::GetCurrentScene() const
{
    return m_pCurrentScene;
}