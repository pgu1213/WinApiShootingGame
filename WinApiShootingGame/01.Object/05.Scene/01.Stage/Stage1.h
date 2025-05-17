#pragma once
#include "../CScene.h"

class Stage1 : public CScene
{
public:
    Stage1();
    virtual ~Stage1();
public:
    virtual void Init(Entity id, EntityType type) override;
};

