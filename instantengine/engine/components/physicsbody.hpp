// Physics Body

#pragma once

#include "basecomponent.hpp"
#include "transform.hpp"

#include <string>
#include <map>

// Struct to store data for onWall, onGround, and onCeiling flags
struct CollisionData {
    Instant::Vector2 selfPast;
    Instant::Vector2 otherPast;
    std::weak_ptr<Transform> other;
};

struct PhysicsBody : public BaseComponent {
    bool onGround = false;
    bool onCeiling = false;
    bool onWall = false;
    
    std::map<std::string, CollisionData> collisions;  // Stored flag data
    
    float mass = 0.0f;  // For future use in more complex physics system
    
    float friction = 1.0f;  // In case you want to slow sliding, for future use
};
