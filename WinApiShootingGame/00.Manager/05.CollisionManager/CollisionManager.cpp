#include "../../pch.h"
#include "CollisionManager.h"
#include "../02.SceneManager/SceneManager.h"
#include "../../01.Object/05.Scene/CScene.h"
#include "../../03.System/02_Collider/ColliderSystem.h"
#include "../../03.System/00_Transform/TransformSystem.h"
#include "../../02.Component/Collider.h"
#include "../../02.Component/Transform.h"

CollisionManager::CollisionManager(SceneManager* sceneMgr) :sceneManager(sceneMgr)
{

}

bool CollisionManager::CheckBoxCollision(const Transform& transform_a, const Collider& collider_a, const Transform& transform_b, const Collider& collider_b)
{
    float ax = transform_a.position.x + collider_a.offset.x;
    float ay = transform_a.position.y + collider_a.offset.y;
    float bx = transform_b.position.x + collider_b.offset.x;
    float by = transform_b.position.y + collider_b.offset.y;

    return (abs(ax - bx) * 2 < (collider_a.size.x + collider_b.size.x)) &&
        (abs(ay - by) * 2 < (collider_a.size.y + collider_b.size.y));
}

bool CollisionManager::CheckCircleCollision(const Transform& ta, const Collider& ca, const Transform& tb, const Collider& cb)
{
    float ax = ta.position.x;
    float ay = ta.position.y;
    float bx = tb.position.x;
    float by = tb.position.y;

    // 각 위치값을 빼서 둘 사이의 거리값을 나타내줌
    float dx = bx - ax;
    float dy = by - ay;

    // 각 x,y 반지름 길이를 다 더해줌
    float sumRadiusX = ca.radiusX + cb.radiusX;
    float sumRadiusY = ca.radiusY + cb.radiusY;

    // 두 원사이 거리와, 반지름 길이를 나눠준다.
    float nx = dx / sumRadiusX;
    float ny = dy / sumRadiusY;

    // 만약 둘 사이가 떨어져 있다면, dx,dy의 거리가 sumRadius값 보다 클테니 1보다 크게 
    // 나오게 된다. 그러므로, 두 콜라이더가 접촉되는 순간, 1보다 작아지게 된다.
    return (nx * nx + ny * ny) <= 1.0f;
}

void CollisionManager::ProcessCollisions()
{
    vector<CActor*> entities;

    for (auto& [id, obj] : *sceneManager->GetCurrentScene()->GetSceneObjectList()) {
        if (obj->GetComponent<ColliderSystem>() && obj->GetComponent<TransformSystem>()) {
            entities.push_back(obj);
        }
    }

    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            CActor* a = entities[i];
            CActor* b = entities[j];

            auto* aCol = a->GetComponent<ColliderSystem>();
            auto* bCol = b->GetComponent<ColliderSystem>();
            auto* aTrans = a->GetComponent<TransformSystem>();
            auto* bTrans = b->GetComponent<TransformSystem>();
            const Collider& colliderA = aCol->GetData();
            const Collider& colliderB = bCol->GetData();

            bool collided = false;

            if (colliderA.colType == ColliderType::Box && colliderB.colType == ColliderType::Box) {
                collided = CheckBoxCollision(aTrans->GetData(), colliderA, bTrans->GetData(), colliderB);
            }
            else if (colliderA.colType == ColliderType::Circle && colliderB.colType == ColliderType::Circle) {
                collided = CheckCircleCollision(aTrans->GetData(), colliderA, bTrans->GetData(), colliderB);
            }

            if (collided) {
                aCol->InvokeCollisionEvent(b);
                bCol->InvokeCollisionEvent(a);
            }
        }
    }
}
