#pragma once
#include "../CScene.h"

class Stage2 : public CScene
{
public:
    Stage2();
    virtual ~Stage2();
public:
    virtual void Init(Entity id, EntityType type) override;
};

