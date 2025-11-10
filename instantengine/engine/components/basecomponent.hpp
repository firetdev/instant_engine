// Base component struct

#pragma once

#include <memory>

class Entity;  // Forward declaration

class BaseComponent {
public:
    virtual ~BaseComponent() = default;
    
    std::weak_ptr<Entity> parent;
};
