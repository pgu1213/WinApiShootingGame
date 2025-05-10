#include "../../99_Default/pch.h"
#include "CollisionManager.h"
#include "../../00_MainGame/MainGame.h"
#include "../../01_System/02_Collider/ColliderSystem.h"
#include "../../01_System/00_Transform/TransformSystem.h"
#include "../../02_Component/Collider.h"
#include "../../02_Component/Transform.h"

CollisionManager::CollisionManager(MainGame* mainGame):mainGame(mainGame)
{

}

bool CollisionManager::CheckCollision(const Transform& transform_a, const Collider& collider_a, const Transform& transform_b, const Collider& collider_b)
{
    float ax = transform_a.position.x + collider_a.offset.x;
    float ay = transform_a.position.y + collider_a.offset.y;
    float bx = transform_b.position.x + collider_b.offset.x;
    float by = transform_b.position.y + collider_b.offset.y;

    return (abs(ax - bx) * 2 < (collider_a.size.x + collider_b.size.x)) &&
        (abs(ay - by) * 2 < (collider_a.size.y + collider_b.size.y));
}

void CollisionManager::ProcessCollisions()
{
    vector<Entity> entities;

    for (auto& [id, table] : *mainGame->GetObjectTable()) {
        if (table.count(typeid(ColliderSystem)) && table.count(typeid(TransformSystem))) {
            entities.push_back(id);
        }
    }

    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            Entity a = entities[i];
            Entity b = entities[j];

            auto* aCol = mainGame->GetComponent<ColliderSystem>(a);
            auto* bCol = mainGame->GetComponent<ColliderSystem>(b);
            auto* aTrans = mainGame->GetComponent<TransformSystem>(a);
            auto* bTrans = mainGame->GetComponent<TransformSystem>(b);

            if (CheckCollision(aTrans->GetData(), aCol->GetData(),
                bTrans->GetData(), bCol->GetData())) {
                aCol->InvokeCollisionEvent(b);
                bCol->InvokeCollisionEvent(a);
            }
        }
    }
}
