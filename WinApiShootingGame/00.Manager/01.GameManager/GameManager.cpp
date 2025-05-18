#include "../../pch.h"
#include "GameManager.h"
#include "../02.SceneManager/SceneManager.h"
#include "../03.TimeManager/TimeManager.h"
#include "../05.CollisionManager/CollisionManager.h"

#include "../../01.Object/00.Default/CObject.h"
#include "../../01.Object/01.Actor/CActor.h"
#include "../../01.Object/05.Scene/CScene.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	delete collisionManager;
	SceneManager::GetInstance()->Release();
}

// 씬 관련 설정
bool GameManager::Init()
{
	srand(static_cast<unsigned int>(time(NULL)));

	currentEntityID = 0;
	hdc = GetDC(g_hWnd);

	SceneManager::GetInstance()->Init();

	collisionManager = new CollisionManager(SceneManager::GetInstance());

	return true;
}

// 씬을 Update 하기 위함
void GameManager::Update(float DeltaTime)
{
	if (DeltaTime < 0.0f)
	{
		return; // 델타 시간이 이상하게 나오면 업데이트 하지 않음
	}

	SceneManager::GetInstance()->Update(DeltaTime);

	collisionManager->ProcessCollisions();

	CheckStageClear();
}

void GameManager::Render(HDC hdc)
{
	Vector2 screenSize = GetScreenSize();

	// 메모리 DC 생성
	HDC memHDC = CreateCompatibleDC(hdc);

	// 백 버퍼 비트맵 생성
	HBITMAP memBitmap = CreateCompatibleBitmap(hdc, screenSize.x, screenSize.y);
	if (memBitmap == NULL)
	{
		DeleteDC(memHDC);
		return;
	}

	// 기존 비트맵을 메모리 DC에 선택
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memHDC, memBitmap);

	// 메모리 DC에 그리기
	RECT clientRect = { 0, 0, screenSize.x, screenSize.y };
	HBRUSH hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	FillRect(memHDC, &clientRect, hbrBackground);

	SceneManager::GetInstance()->Render(memHDC);

	// 메모리 DC의 내용을 실제 윈도우에 복사
	BitBlt(hdc, 0, 0, screenSize.x, screenSize.y, memHDC, 0, 0, SRCCOPY);

	SelectObject(memHDC, oldBitmap); // 메모리 DC에 원래 비트맵 되돌리기
	DeleteObject(memBitmap); // 비트맵 해제
	DeleteDC(memHDC); // 메모리 DC 해제
}

// 엔티티의 생성은 유일해야 함.
Entity GameManager::CreateEntity()
{
	return ++currentEntityID == NULL ? 0 : currentEntityID;
}

void GameManager::CheckStageClear()  
{  
   const auto* sceneObjectList = SceneManager::GetInstance()->GetCurrentScene()->GetSceneObjectList();  

   if (sceneObjectList == nullptr)  
   {  
       return;  
   }  

   for (const auto& obj : *sceneObjectList)  
   {  
       if (obj.second->GetType() == EntityType::Enemy)
       {  
		   return;
       } 
   }
   SceneManager::GetInstance()->ReleaseCurrentScene();
   SceneManager::GetInstance()->ChangeScene("Stage2");
}

Vector2 GameManager::GetScreenSize()
{
	RECT winRect;
	float width = 0;
	float height = 0;
	if (g_hWnd != NULL)
	{
		GetClientRect(g_hWnd, &winRect);

		width = static_cast<float>(winRect.right - winRect.left);
		height = static_cast<float>(winRect.bottom - winRect.top);
	}
	return Vector2{ width, height };
}
