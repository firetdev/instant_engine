// CollisionBox struct

#pragma once

#include "../instant.hpp"
#include "basecomponent.hpp"

struct CollisionBox : public BaseComponent {
    Instant::Vector2 position; // Top-left corner
    Instant::Vector2 size;     // Width and height
};
