#pragma once

class ComponentSystem;
using ComponentTable = map<type_index, ComponentSystem*>;

class CObject
{
public:
	CObject(const string& Name = "Object");

public:
	virtual void Init(Entity id, EntityType type, ComponentTable compTable);
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hdc);
	virtual void Release();

	// unsigned int GetObjectID() const; // 오브젝트 ID 반환
	const Entity& GetId() const;
	const EntityType& GetType() const;
	const string& GetObjectName() const; // 오브젝트 이름 반환
	bool IsValid() const; // 객체가 유효한지 확인
	bool m_bIsGCMark; // GC 마킹 여부
private:
	Entity m_id;
	EntityType m_type;
	ComponentTable m_componentTable;
	//atomic<unsigned int> m_NextObjectID; // 다음 출력을 위한 임시 UID
	//unsigned int m_ObjectID; // 임시 UID
	string m_ObjectName;     // 객체의 이름
	bool m_bIsValid; // 객체가 유효한 상태인지?

public:
	template <typename T>
	const T* GetComponent()
	{
		auto comp = m_componentTable.find(typeid(T));
		if (comp != m_componentTable.end()) {
			return dynamic_cast<T*>(comp->second);
		}
		return nullptr;
	}
};
