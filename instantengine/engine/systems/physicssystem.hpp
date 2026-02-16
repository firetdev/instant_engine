// Physics System class

// TODO: Add dynamic gravity

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

struct CollisionResult {
    float t = 1.0f;  // Time of Impact (0.0 to 1.0). 1.0 means no collision.
    Instant::Vector2 normal = {0, 0};  // Collision normal (which side was hit)
    bool collided = false;  // Did a collision occur?
    float pushDistance = 0.0f;  // If they're overlapping, by how far
};

class PhysicsSystem : public BaseSystem {
public:
    CollisionResult SweptAABB(
        const std::shared_ptr<CollisionBox>& aBox, const std::shared_ptr<Transform>& aTransform, const Instant::Vector2& velocity,
        const std::shared_ptr<CollisionBox>& bBox, const std::shared_ptr<Transform>& bTransform)
    {
        // Epsilon to handle floating point issues near zero
        const float EPSILON = 1e-6f;

        // Calculate the world-space minimum and maximum points for both AABBs
        
        // Moving Box A Bounds (Current Position)
        float aMinX = aTransform->position.x + aBox->position.x;
        float aMaxX = aMinX + aBox->size.x;
        float aMinY = aTransform->position.y + aBox->position.y;
        float aMaxY = aMinY + aBox->size.y;

        // Static Box B Bounds
        float bMinX = bTransform->position.x + bBox->position.x;
        float bMaxX = bMinX + bBox->size.x;
        float bMinY = bTransform->position.y + bBox->position.y;
        float bMaxY = bMinY + bBox->size.y;
        
        // Calculate the distance to separate and the distance to overlap on each axis
        float x_dist_enter, x_dist_exit;
        float y_dist_enter, y_dist_exit;

        // Determine the distance between the two boxes along the X-axis
        if (velocity.x > 0) {
            // Moving Right: Distance to entry is distance from A's right to B's left
            x_dist_enter = bMinX - aMaxX;
            // Distance to exit is distance from A's left to B's right
            x_dist_exit = bMaxX - aMinX;
        } else { // velocity.x <= 0 (Moving Left or Static)
            // Moving Left: Distance to entry is distance from A's left to B's right
            x_dist_enter = bMaxX - aMinX;
            // Distance to exit is distance from A's right to B's left
            x_dist_exit = bMinX - aMaxX;
        }

        // Determine the distance between the two boxes along the Y-axis
        if (velocity.y > 0) {
            // Moving Down: Distance to entry is distance from A's bottom to B's top
            y_dist_enter = bMinY - aMaxY;
            // Distance to exit is distance from A's top to B's bottom
            y_dist_exit = bMaxY - aMinY;
        } else { // velocity.y <= 0 (Moving Up or Static)
            // Moving Up: Distance to entry is distance from A's top to B's bottom
            y_dist_enter = bMaxY - aMinY;
            // Distance to exit is distance from A's bottom to B's top
            y_dist_exit = bMinY - aMaxY;
        }
        
        // Calculate Time of Entry and Exit

        float t_entry_x, t_exit_x;
        if (std::abs(velocity.x) < EPSILON) {
            if (aMaxX <= bMinX || aMinX >= bMaxX) {
                // Separated on X axis at t=0, so no collision is possible.
                return {1.0f, {0, 0}, false};
            }
            // If no movement on X, set times to infinity/negative infinity
            // to effectively ignore this axis for TOI calculation, but ensure overlap check below.
            t_entry_x = -std::numeric_limits<float>::infinity();
            t_exit_x = std::numeric_limits<float>::infinity();
        } else {
            t_entry_x = x_dist_enter / velocity.x;
            t_exit_x = x_dist_exit / velocity.x;
        }

        float t_entry_y, t_exit_y;
        if (std::abs(velocity.y) < EPSILON) {
            if (aMaxY <= bMinY || aMinY >= bMaxY) {
                // Separated on Y axis at t=0, so no collision is possible.
                return {1.0f, {0, 0}, false};
            }
            t_entry_y = -std::numeric_limits<float>::infinity();
            t_exit_y = std::numeric_limits<float>::infinity();
        } else {
            t_entry_y = y_dist_enter / velocity.y;
            t_exit_y = y_dist_exit / velocity.y;
        }
        
        // Find the max entry time and min exit time across all axes
        float t_entry = std::max(t_entry_x, t_entry_y);
        float t_exit = std::min(t_exit_x, t_exit_y);
        
        CollisionResult result;

        // Check if they were already overlapping
        bool isOverlapping = (aMaxX > bMinX && aMinX < bMaxX) &&
                             (aMaxY > bMinY && aMinY < bMaxY);
        
        if (isOverlapping) {
            result.collided = true;
            result.t = 0.0f;

            // Calculate overlap on all 4 sides
            float overlapLeft   = aMaxX - bMinX;
            float overlapRight  = bMaxX - aMinX;
            float overlapTop    = aMaxY - bMinY;
            float overlapBottom = bMaxY - aMinY;

            // Find the smallest overlap
            float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

            if (minOverlap == overlapLeft) {
                result.normal = {-1.0f, 0.0f};
                result.pushDistance = overlapLeft;
            } else if (minOverlap == overlapRight) {
                result.normal = {1.0f, 0.0f};
                result.pushDistance = overlapRight;
            } else if (minOverlap == overlapTop) {
                result.normal = {0.0f, -1.0f};
                result.pushDistance = overlapTop;
            } else { // overlapBottom
                result.normal = {0.0f, 1.0f};
                result.pushDistance = overlapBottom;
            }
            return result;
        }
        
        // Check if collision occurred within the movement range [0, 1]
        if (t_entry > t_exit || t_entry < 0.0f || t_entry > 1.0f) {
            // No collision, or collision happened outside of the movement range, or already separated
            result.collided = false;
            result.t = 1.0f;
            return result;
        }
        
        // Collision happened. Set the time of impact.
        result.collided = true;
        result.t = t_entry;

        // Determine the collision normal
        if (t_entry_x > t_entry_y) {
            // Collision happened first/most restrictively on the X-axis
            if (x_dist_enter > 0) {
                result.normal = {-1.0f, 0.0f}; // Hit from the left (moving right)
            } else {
                result.normal = {1.0f, 0.0f};  // Hit from the right (moving left)
            }
        } else {
            // Collision happened first/most restrictively on the Y-axis
            if (y_dist_enter > 0) {
                result.normal = {0.0f, -1.0f}; // Hit from above (moving down)
            } else {
                result.normal = {0.0f, 1.0f};  // Hit from below (moving up)
            }
        }

        return result;
    }
    
    void update(const std::vector<std::shared_ptr<Entity>>& entities) {
        struct ColliderInfo {
            std::shared_ptr<Entity> entity;
            std::shared_ptr<Transform> transform;
            std::vector<std::shared_ptr<CollisionBox>> physicalBoxes;
        };

        std::vector<ColliderInfo> colliders;
        
        for (auto& entityB : entities) {
            // Check for Transform
            auto transformB = entityB->getComponents<Transform>();
            if (transformB.empty()) continue;

            // Check for PhysicsBody (or child, e.g., StaticBody, CharacterBody)
            auto bodyB = entityB->getComponents<PhysicsBody>();
            if (bodyB.empty()) continue; // Checks for PhysicsBody or any class that inherits it

            // Find physical CollisionBoxes
            std::vector<std::shared_ptr<CollisionBox>> physicalBoxes;
            auto boxesB = entityB->getComponents<CollisionBox>();
            for (auto& boxB : boxesB) {
                if (boxB->isPhysical) { // Assuming isPhysical is a bool, or correctly tagged
                    physicalBoxes.push_back(boxB);
                }
            }

            // Check if at least one physical CollisionBox exists
            if (!physicalBoxes.empty()) {
                colliders.push_back({entityB, transformB[0], physicalBoxes});
            }
        }
        
        for (auto& entityA : entities) {
            // Get physics body
            auto bodies = entityA->getComponents<PhysicsBody>();
            if (bodies.empty()) continue;
            std::shared_ptr<PhysicsBody> bodyA = bodies[0];

            // Move body
            auto characterBodyA = std::dynamic_pointer_cast<CharacterBody>(bodyA);

            // Check if the cast succeeded. If it did, this is a CharacterBody.
            if (characterBodyA) {
                // Calculate displacement
                Instant::Vector2 displacement = characterBodyA->velocity * Instant::delta;
                
                // Reset flags
                if (characterBodyA->onGround && displacement.y < 0) {
                    characterBodyA->onGround = false;
                }
                if (characterBodyA->onCeiling && displacement.y != 0) {
                    characterBodyA->onCeiling = false;
                }
                if (characterBodyA->onWall && displacement.x != 0) {
                    characterBodyA->onWall = false;
                }

                // Update gravity
                if (characterBodyA->dynamicGravity == false) {
                    characterBodyA->gravity = Instant::gravity;
                } else {
                    // Body is using dynamic gravity--will need to add logic later
                }
                
                // Get transform
                auto transformA = entityA->getComponents<Transform>();
                if (transformA.empty()) continue;
                std::shared_ptr<Transform> tA = transformA[0]; // Get the transform
                std::shared_ptr<Transform> tB;
                
                // Set flags
                // If one of the bodies involved in a collision has moved, the flags are reset
                if (characterBodyA->onGround) {
                    auto other = characterBodyA->collisions["ground"].other.lock();
                    if (tA->position != characterBodyA->collisions["ground"].selfPast
                        || characterBodyA->collisions["ground"].otherPast != other->position)
                    {
                        characterBodyA->onGround = false;
                    }
                }
                
                if (characterBodyA->onCeiling) {
                    auto other = characterBodyA->collisions["ceiling"].other.lock();
                    if (tA->position != characterBodyA->collisions["ceiling"].selfPast
                        || characterBodyA->collisions["ceiling"].otherPast != other->position)
                    {
                        characterBodyA->onCeiling = false;
                    }
                }
                
                if (characterBodyA->onWall) {
                    auto other = characterBodyA->collisions["wall"].other.lock();
                    if (tA->position != characterBodyA->collisions["wall"].selfPast
                        || characterBodyA->collisions["wall"].otherPast != other->position)
                    {
                        characterBodyA->onWall = false;
                    }
                }
                
                // Get physical CollisionBoxes for entityA
                std::vector<std::shared_ptr<CollisionBox>> physicalBoxesA;
                auto boxesA = entityA->getComponents<CollisionBox>();
                for (auto& boxA : boxesA) {
                    if (boxA->isPhysical) {
                        physicalBoxesA.push_back(boxA);
                    }
                }
                if (physicalBoxesA.empty()) continue; // Entity A has nothing physical to collide with/against
                
                // Find the earliest collision time (t_min) across all potential collisions
                CollisionResult earliestCollision;
                earliestCollision.t = 1.0f; // Initialize with no collision (full movement allowed)
                
                // Check all moving A-boxes against all static B-boxes
                for (auto& boxA : physicalBoxesA) {
                    for (const auto& colliderB : colliders) {
                        if (colliderB.entity == entityA) continue; // Skip self
                        
                        for (auto& boxB : colliderB.physicalBoxes) {
                            CollisionResult result = SweptAABB(boxA, tA, displacement,
                                                               boxB, colliderB.transform);
                            
                            // If a collision occurs earlier than the current earliest, update it
                            if (result.collided && result.t < earliestCollision.t) {
                                earliestCollision = result;
                                tB = colliderB.transform;
                            }
                        }
                    }
                }
                
                // Apply movement up to the collision point, or full movement if no collision
                float t_move = earliestCollision.t;
                
                // Move up to the point of impact
                tA->position.x += displacement.x * t_move;
                tA->position.y += displacement.y * t_move;
                
                // If we are overlapping (t is 0), nudge the player out
                if (earliestCollision.collided && earliestCollision.t == 0.0f) {
                    const float EPSILON = 0.01f;  // A tiny extra bit to ensure they aren't touching
                    tA->position.x += earliestCollision.normal.x * (earliestCollision.pushDistance + EPSILON);
                    tA->position.y += earliestCollision.normal.y * (earliestCollision.pushDistance + EPSILON);
                }
                
                // Kill velocity on collision axes
                if (earliestCollision.normal.x != 0)
                    characterBodyA->velocity.x = 0;

                if (earliestCollision.normal.y != 0)
                    characterBodyA->velocity.y = 0;
                
                if (earliestCollision.collided) {
                    Instant::Vector2 n = earliestCollision.normal;

                    // Update flags
                    if (n.y == -1) {
                        characterBodyA->onGround = true;
                        
                        // Data on flag activation
                        characterBodyA->collisions["ground"] = {
                            tA->position, tB->position, tB
                        };
                    }
                    if (n.y ==  1) {
                        characterBodyA->onCeiling = true;
                        
                        // Data on flag activation
                        characterBodyA->collisions["ceiling"] = {
                            tA->position, tB->position, tB
                        };
                    }
                    if (n.x !=  0) {
                        characterBodyA->onWall = true;
                        
                        // Data on flag activation
                        characterBodyA->collisions["wall"] = {
                            tA->position, tB->position, tB
                        };
                    }
                }
                
                // Remaining velocity, for sliding
                Instant::Vector2 remainingVel = displacement * (1.0f - t_move);
                
                CollisionResult slideCollision;

                // Check all moving A-boxes against all static B-boxes (again)
                for (auto& boxA : physicalBoxesA) {
                    for (const auto& colliderB : colliders) {
                        if (colliderB.entity == entityA) continue; // Skip self
                        
                        for (auto& boxB : colliderB.physicalBoxes) {
                            CollisionResult result = SweptAABB(boxA, tA, remainingVel,
                                                               boxB, colliderB.transform);
                            
                            // If a collision occurs earlier than the current earliest, update it
                            if (result.collided && result.t < earliestCollision.t) {
                                slideCollision = result;
                            }
                        }
                    }
                }
                
                // Apply movement up to the collision point, or full movement if no collision
                float t_slide = slideCollision.t;
                
                // Move up to the point of impact
                tA->position.x += remainingVel.x * t_slide;
                tA->position.y += remainingVel.y * t_slide;
                
                // Kill velocity on collision axes
                if (slideCollision.normal.x != 0)
                    characterBodyA->velocity.x = 0;

                if (slideCollision.normal.y != 0)
                    characterBodyA->velocity.y = 0;
                
                if (slideCollision.collided) {
                    Instant::Vector2 n = slideCollision.normal;

                    // Update flags
                    if (n.y == -1) {
                        characterBodyA->onGround = true;
                        
                        // Data on flag activation
                        characterBodyA->collisions["ground"] = {
                            tA->position, tB->position, tB
                        };
                    }
                    if (n.y ==  1) {
                        characterBodyA->onCeiling = true;
                        
                        // Data on flag activation
                        characterBodyA->collisions["ceiling"] = {
                            tA->position, tB->position, tB
                        };
                    }
                    if (n.x !=  0) {
                        characterBodyA->onWall = true;
                        
                        // Data on flag activation
                        characterBodyA->collisions["wall"] = {
                            tA->position, tB->position, tB
                        };
                    }
                }
                
                if (t_move < 1.0) {
                    // Collision occured
                }
            }
        }
    }
};
