// Base system class

#pragma once

#include "../entity.hpp"

#include <vector>
#include <memory>

class BaseSystem {
public:
    virtual ~BaseSystem() = default; // Required for polymorphism

    virtual void update(const std::vector<std::shared_ptr<Entity>>& entities) = 0;
};
