#pragma once

class ComponentSystem;
using ComponentTable = map<type_index, ComponentSystem*>;

class CObject
{
public:
	CObject();
	virtual ~CObject();

public:
	virtual void Init(Entity id, EntityType type);
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hdc);
	virtual void Release();

	const Entity& GetId() const;
	const EntityType& GetType() const;

	bool IsValid() const; // 객체가 유효한지 확인
	bool m_bIsGCMark; // GC 마킹 여부
protected:
	Entity m_id;
	EntityType m_type;
	ComponentTable m_componentTable;

	bool m_bIsValid; // 객체가 유효한 상태인지?
public:
	template <typename T>
	const T* GetComponent() const
	{
		auto comp = m_componentTable.find(typeid(T));
		if (comp != m_componentTable.end()) {
			return dynamic_cast<T*>(comp->second);
		}
		return nullptr;
	}
};
