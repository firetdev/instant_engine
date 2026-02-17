// CollisionSystem class

#pragma once

#include "../entity.hpp"
#include "../components/collisionbox.hpp"
#include "../components/transform.hpp"
#include "basesystem.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class CollisionSystem : public BaseSystem {
public:
    bool isColliding(std::shared_ptr<CollisionBox> a,
                     std::shared_ptr<CollisionBox> b)
    {
        // Get transforms
        auto aTransforms = a->getParent()->getComponents<Transform>();
        auto bTransforms = b->getParent()->getComponents<Transform>();

        if (aTransforms.empty() || bTransforms.empty())
            return false;

        auto aT = aTransforms[0];
        auto bT = bTransforms[0];

        // Compute world-space bounding boxes
        float aLeft   = aT->position.x + a->position.x;
        float aRight  = aLeft + a->size.x;
        float aTop    = aT->position.y + a->position.y;
        float aBottom = aTop + a->size.y;

        float bLeft   = bT->position.x + b->position.x;
        float bRight  = bLeft + b->size.x;
        float bTop    = bT->position.y + b->position.y;
        float bBottom = bTop + b->size.y;

        // AABB test
        return (aLeft < bRight &&
                aRight > bLeft &&
                aTop < bBottom &&
                aBottom > bTop);
    }

    void update(const std::vector<std::shared_ptr<Entity>>& entities) {
        for (auto& entityA : entities) {
            auto colsA = entityA->getComponents<CollisionBox>();
            if (colsA.empty()) continue;
            
            for (auto& colA : colsA) {
                if (colA->isPhysical) continue;

                colA->collidingWith.clear();

                for (auto& entityB : entities) {
                    auto colsB = entityB->getComponents<CollisionBox>();
                    if (colsB.empty()) continue;

                    for (auto& colB : colsB) {
                        if (colA == colB) continue; // skip self
                        if (colB->isPhysical) continue;
                        
                        if (isColliding(colA, colB)) {
                            colA->collidingWith.emplace_back(colB->getParent());
                        }
                    }
                }
            }
        }
    }
};
