#pragma once

#include "../engine.hpp"
#include "basecomponent.hpp"

struct Transform : public BaseComponent {
    Instant::Vector2 position;  // Position
    Instant::Vector2 scale;  // Scale
};
