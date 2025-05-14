#pragma once
class CObject
{
public:
	CObject();
	virtual ~CObject() = default;

public:
	virtual void Init(Entity id, EntityType type) = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;

	const Entity& GetId() const;
	const EntityType& GetType() const;

	bool IsValid() const; // 객체가 유효한지 확인
	bool m_bIsGCMark; // GC 마킹 여부
protected:
	Entity m_id;
	EntityType m_type;

	bool m_bIsValid; // 객체가 유효한 상태인지?
};
