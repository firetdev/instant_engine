// Base system class

#pragma once

#include "../entity.hpp"

#include <vector>
#include <memory>

class BaseSystem {
public:
    virtual void update(std::vector<std::shared_ptr<Entity>>);
};
