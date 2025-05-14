#pragma once
#include "../00.Default/CObject.h"

class ComponentSystem;
class IRenderer;
using ComponentTable = map<type_index, ComponentSystem*>;

class CActor : public CObject
{
public:
	CActor();
	virtual ~CActor();
protected:
	ComponentTable m_componentTable;
	IRenderer* render;
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

// CObject을(를) 통해 상속됨
public:
	virtual void Init(Entity id, EntityType type) override;
	virtual void Update(float DeltaTime) override;	
	virtual void Render(HDC hdc)override;
	virtual void Release() override;

};

