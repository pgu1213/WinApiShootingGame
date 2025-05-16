#pragma once
#include "../../03.System/IRenderer.h"

struct SpriteRenderer;
struct Transform;

class SpriteRendererSystem : public ComponentSystem, public IDataProvider<SpriteRenderer>, public IRenderer 
{
private:
	SpriteRenderer* m_render;
	HDC hdc;
public:
	SpriteRendererSystem(CActor* owner, HDC hdc);
	virtual ~SpriteRendererSystem();
	virtual void Init()override;
	virtual void Update(float _deltaTime) override;
	virtual void Render(HDC hdc) override;
	 SpriteRenderer& GetData()const;
	SpriteRenderer& GetModifyData();
};

