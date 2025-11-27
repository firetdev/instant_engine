// Physics Body

#pragma once

#include "basecomponent.hpp"

#include <string>

struct PhysicsBody : public BaseComponent {
    bool onGround = false;
    
    float mass = 0.0f;  // For future use in more complex physics system
};
