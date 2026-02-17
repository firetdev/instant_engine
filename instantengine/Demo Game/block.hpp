#pragma once

#include "../engine/engine.hpp"

class Block : public Entity {
public:
    Block(int id, const std::string& name)
            : Entity(id, name) {}
    
    Block(int id, const std::string& name, Instant::Vector2 pos)
            : Entity(id, name), startPos(pos) {}
    
    Instant::Vector2 startPos;
    
    void update() override {}

    void setup() override {
        // Create components
        auto transform = std::make_shared<Transform>();
        transform->position = startPos;
        transform->scale = {1.0f, 1.0f};

        auto sprite = std::make_shared<Sprite>("player.png");
        
        auto collider = std::make_shared<CollisionBox>();
        collider->size = {64, 64};  // Example size
        collider->isPhysical = true;

        auto body = std::make_shared<StaticBody>();
        
        // Add them to the entity instance
        addComponent(transform);
        addComponent(sprite);
        addComponent(collider);
        addComponent(body);

        // Can also run custom Player-specific logic here
        std::cout << "Block entity has been initialized.\n";
    }
};
