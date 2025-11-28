// Physics Body

#pragma once

#include "basecomponent.hpp"

#include <string>

struct PhysicsBody : public BaseComponent {
    bool onGround = false;
    bool onCeiling = false;
    bool onWall = false;
    
    float mass = 0.0f;  // For future use in more complex physics system
    
    float friction = 1.0f;  // In case you want to slow sliding, for future use
};
