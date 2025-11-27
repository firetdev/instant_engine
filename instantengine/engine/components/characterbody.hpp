// Character Body

#pragma once

#include "../instant.hpp"
#include "physicsbody.hpp"

struct CharacterBody : public PhysicsBody {
    Instant::Vector2 velocity;
    
    float maxSpeed = 100000000000;  // Maximum speed
};
