#pragma once

#include "../engine/engine.hpp"

class Player : public Entity {
public:
    Player(int id, const std::string& name)
            : Entity(id, name) {}
    
    void update() override {
        getComponents<CharacterBody>()[0]->velocity.x = 0;
        
        if (getComponents<CharacterBody>()[0]->onGround == false)
            getComponents<CharacterBody>()[0]->applyGravity();
        else
            getComponents<CharacterBody>()[0]->velocity.y = 0;
        
        if (Input::inputs["w"] && getComponents<CharacterBody>()[0]->onGround == true) {
            getComponents<CharacterBody>()[0]->velocity.y = -400;
        }
        if (Input::inputs["a"]) {
            getComponents<CharacterBody>()[0]->velocity.x = -160;
        }
        if (Input::inputs["d"]) {
            getComponents<CharacterBody>()[0]->velocity.x = 160;
        }
        
        // Restart if the player falls
        if (getComponents<Transform>()[0]->position.y > 1000) {
            getComponents<Transform>()[0]->position = {100, 100};
            getComponents<CharacterBody>()[0]->velocity.y = 0;
        }
    }

    void setup() override {
        // CHANGE ENGINE GRAVITY
        Instant::gravity.y = 400;
        
        // Create components
        auto transform = std::make_shared<Transform>();
        transform->position = {100, 100};
        transform->scale = {1.0f, 1.0f};

        auto sprite = std::make_shared<Sprite>("player.png");
        
        auto collider = std::make_shared<CollisionBox>();
        collider->size = {64, 64};  // Example size
        collider->isPhysical = true;
        
        auto body = std::make_shared<CharacterBody>();

        // Add them to the entity instance
        addComponent(transform);
        addComponent(sprite);
        addComponent(collider);
        addComponent(body);

        // Can also run custom Player-specific logic here
        std::cout << "Player entity has been initialized.\n";
    }
};
