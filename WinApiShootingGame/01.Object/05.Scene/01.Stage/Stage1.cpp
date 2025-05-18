#include "../../../pch.h"
#include "Stage1.h"

Stage1::Stage1() : CScene("Stage1")
{
}

Stage1::~Stage1()
{
}

void Stage1::Init(Entity id, EntityType type)
{
    GeneratePlayer();

    // GenerateBoss1();
    
    GenerateEnemy();
    GenerateEnemy();
    GenerateEnemy();

}