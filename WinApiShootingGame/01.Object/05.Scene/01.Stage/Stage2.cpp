#include "../../../pch.h"
#include "Stage2.h"

Stage2::Stage2() : CScene("Stage2")
{
}

Stage2::~Stage2()
{
}

void Stage2::Init(Entity id, EntityType type)
{
    GeneratePlayer();

    GenerateEnemy();
    GenerateEnemy();
    GenerateEnemy();

    GenerateBoss1();
}