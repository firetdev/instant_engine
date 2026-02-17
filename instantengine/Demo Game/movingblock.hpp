#pragma once

#include "../engine/engine.hpp"

class MovingBlock : public Entity {
public:
    MovingBlock(int id, const std::string& name, Instant::Vector2 pos, int velo, int ystart, int ygoal)
            : Entity(id, name), vel(velo), y1(ystart), y2(ygoal), next(y2), startPos(pos) {}
    
    int vel, y1, y2;
    int next;
    float lastY;
    
    Instant::Vector2 startPos;
    
    void update() override {
        if (getComponents<Transform>()[0]->position.x != startPos.x)
            getComponents<Transform>()[0]->position.x = startPos.x;
        if (getComponents<Transform>()[0]->position.y > next)
            getComponents<CharacterBody>()[0]->velocity.y = -vel;
        else
            getComponents<CharacterBody>()[0]->velocity.y = vel;
        
        if (lastY < next && getComponents<Transform>()[0]->position.y > next) {
            if (next == y1)
                next = y2;
            else
                next = y1;
        }
        if (lastY > next && getComponents<Transform>()[0]->position.y < next) {
            if (next == y1)
                next = y2;
            else
                next = y1;
        }
        
        lastY = getComponents<Transform>()[0]->position.y;
    }

    void setup() override {
        // Create components
        auto transform = std::make_shared<Transform>();
        transform->position = startPos;
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
        
        // Add initial velocity
        getComponents<CharacterBody>()[0]->velocity.y = vel;
        
        std::cout << "MovingBlock entity has been initialized.\n";
    }
};
