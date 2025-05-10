#include "../../pch.h"
#include "CollisionManager.h"
#include "../01.GameManager/GameManager.h"
#include "../../03.System/02_Collider/ColliderSystem.h"
#include "../../03.System/00_Transform/TransformSystem.h"
#include "../../02.Component/Collider.h"
#include "../../02.Component/Transform.h"

CollisionManager::CollisionManager(GameManager* gameMgr):gameManager(gameMgr)
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
    vector<CObject*> entities;

    for (auto& [id, obj] : *gameManager->GetEntityTable()) {
        if (obj->GetComponent<ColliderSystem>() && obj->GetComponent<TransformSystem>()) {
            entities.push_back(obj);
        }
    }

    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            CObject* a = entities[i];
            CObject* b = entities[j];

            auto* aCol = a->GetComponent<ColliderSystem>();
            auto* bCol = b->GetComponent<ColliderSystem>();
            auto* aTrans = a->GetComponent<TransformSystem>();
            auto* bTrans = b->GetComponent<TransformSystem>();

            if (CheckCollision(aTrans->GetData(), aCol->GetData(),
                bTrans->GetData(), bCol->GetData())) {
                aCol->InvokeCollisionEvent(b);
                bCol->InvokeCollisionEvent(a);
            }
        }
    }
}
