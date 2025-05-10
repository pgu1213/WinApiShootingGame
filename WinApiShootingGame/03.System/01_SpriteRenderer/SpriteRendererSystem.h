#pragma once
struct SpriteRenderer;
struct Transform;

class SpriteRendererSystem : public ComponentSystem, public IDataProvider<SpriteRenderer>
{
private:
	SpriteRenderer* m_render;
	const Transform& m_transform;
	HDC hdc;
public:
	SpriteRendererSystem(MainGame* maingame, Entity id, HDC hdc);
	virtual ~SpriteRendererSystem();
	virtual void Update() override;
	const SpriteRenderer& GetData()const;
};

