// CollisionBox struct

#pragma once

#include "../instant.hpp"
#include "basecomponent.hpp"

#include <vector>
#include <memory>

struct CollisionBox : public BaseComponent {
    Instant::Vector2 position; // Top-left corner
    Instant::Vector2 size;     // Width and height
    
    bool isPhysical = false;  // Should collider affect movement?

    // List of entities we are currently overlapping with
    std::vector<std::weak_ptr<Entity>> collidingWith;
};
