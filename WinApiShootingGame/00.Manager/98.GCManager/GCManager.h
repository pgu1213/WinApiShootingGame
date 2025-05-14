#pragma once

class CObject;

class GCManager
{
public:
	static void AllObject(CObject* object); // 오브젝트 생성 시 호출 함수 (모든 오브젝트 리스트에 추가)
	static void AddSubscriptionsObject(CObject* object); // 순회 리스트에 추가
	static void RemoveSubscriptionsObject(CObject* object); // 순회 리스트에서 제거
	static void MarkForDelete(CObject* object); // 삭제할 오브젝트를 마킹
	static void CollectGarbage(); // 마킹된 오브젝트 삭제
private:
	static vector<CObject*> m_AllObjectList; // 모든 오브젝트 리스트
	static vector<CObject*> m_ObjectListSet; // 실제 순회하는 오브젝트 리스트
};

