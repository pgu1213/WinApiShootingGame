#include "../../pch.h"
#include "GCManager.h"
#include "../../01.Object/00.Default/CObject.h"

vector<CObject*> GCManager::m_AllObjectList;
vector<CObject*> GCManager::m_ObjectListSet;

void GCManager::AllObject(CObject* object)
{
	if (object == nullptr)
	{
		return;
	}
	m_AllObjectList.push_back(object);
}

void GCManager::AddSubscriptionsObject(CObject* object)
{
	if (object == nullptr)
	{
		return;
	}
	m_ObjectListSet.push_back(object);
}

void GCManager::RemoveSubscriptionsObject(CObject* object)
{
	if (object == nullptr)
	{
		return;
	}
	m_ObjectListSet.erase(remove(m_ObjectListSet.begin(), m_ObjectListSet.end(), object), m_ObjectListSet.end());
}

void GCManager::MarkForDelete(CObject* object)
{
	if (!object->m_bIsGCMark)
	{
		return; // 이미 마킹된 오브젝트는 무시
	}
	
	object->m_bIsGCMark = true; // 마킹

	// TODO - 마킹한 오브젝트가 참조하는 다른 오브젝트들도 마킹 필요
}

void GCManager::CollectGarbage()
{
	for (CObject* ObjectList : m_ObjectListSet)
	{
		MarkForDelete(ObjectList); // 가능한 오브젝트 마킹
	}

	vector<CObject*> TempList; // 임시 리스트

	for (CObject* Object : m_AllObjectList)
	{
		if (Object->m_bIsGCMark) // 마킹된 오브젝트는 삭제
		{
			Object->Release(); // 오브젝트 해제

			delete Object;
		}
		else
		{
			Object->m_bIsGCMark = false; // 다시 초기화
			TempList.push_back(Object); // 마킹되지 않은 오브젝트는 임시 리스트에 추가
		}
	}
	m_AllObjectList = TempList; // 임시 리스트로 교체
}
