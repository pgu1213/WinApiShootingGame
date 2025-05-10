#pragma once
struct SpriteRenderer;
struct Transform;

class SpriteRendererSystem : public ComponentSystem, public IDataProvider<SpriteRenderer>
{
private:
	SpriteRenderer* m_render;
	HDC hdc;
public:
	SpriteRendererSystem(CObject* owner, HDC hdc);
	virtual ~SpriteRendererSystem();
	virtual void Init()override;
	virtual void Update(float _deltaTime) override;
	const SpriteRenderer& GetData()const;
};

