// Character Body

#pragma once

#include "../instant.hpp"
#include "physicsbody.hpp"

struct CharacterBody : public PhysicsBody {
    Instant::Vector2 velocity;
    Instant::Vector2 gravity = {0, 0};
    
    bool onGround = false;
    bool dynamicGravity = false;  // Dynamic gravity is calculated using physics equations and mass of objects
    float maxSpeed = 100000000000;  // Maximum speed
    
    void applyGravity() {
        // Q: Why am I multiplying by delta twice?
        // A: The physics system doesn't ever multiply by delta, so
        // whenever you change the velocity you need to multiply it by delta.
        // However, we also need to multiply gravity by delta so that
        // it accelerates by the gravity constant per second, rather than per frame.
        velocity.x = velocity.x + gravity.x * Instant::delta * Instant::delta;
        velocity.y = velocity.y + gravity.y * Instant::delta * Instant::delta;
    }
};
