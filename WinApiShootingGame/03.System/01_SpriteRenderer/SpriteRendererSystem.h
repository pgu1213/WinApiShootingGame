#pragma once
struct SpriteRenderer;

class SpriteRendererSystem : public ComponentSystem, public IDataProvider<SpriteRenderer>
{
private:
	SpriteRenderer* m_render;
	HDC hdc;
public:
	SpriteRendererSystem(MainGame* maingame, Entity id, HDC hdc);
	virtual ~SpriteRendererSystem();
	virtual void Update() override;
	const SpriteRenderer& GetData()const;
};

