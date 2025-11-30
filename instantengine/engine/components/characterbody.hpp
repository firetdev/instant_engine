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
        velocity.x += gravity.x * Instant::delta;
        velocity.y += gravity.y * Instant::delta;
    }
};
