// Physics System class

#pragma once

#include "../entity.hpp"
#include "../components/collisionbox.hpp"
#include "../components/transform.hpp"
#include "../components/characterbody.hpp"
#include "../components/staticbody.hpp"
#include "basesystem.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class PhysicsSystem : public BaseSystem {
public:
    void update(const std::vector<std::shared_ptr<Entity>>& entities) {
        for (auto& entityA : entities) {
            // Get physics body
            auto bodies = entityA->getComponents<PhysicsBody>();
            if (bodies.empty()) continue;
            std::shared_ptr<PhysicsBody> bodyA = bodies[0];

            // Move body
            auto characterBodyA = std::dynamic_pointer_cast<CharacterBody>(bodyA);

            // Check if the cast succeeded. If it did, this is a CharacterBody.
            if (characterBodyA) {
                auto transformA = entityA->getComponents<Transform>();
                if (transformA.empty()) continue;
                
                bool canMove = true;
                
                // TODO: Add collisions
                
                if (canMove) {
                    transformA[0]->position.x += characterBodyA->velocity.x;
                    transformA[0]->position.y += characterBodyA->velocity.y;
                }
            }
        }
    }
};
