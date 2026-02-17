#pragma once

#include "../engine/engine.hpp"

class Enemy : public Entity {
public:
    Enemy(int id, const std::string& name, Instant::Vector2 pos)
            : Entity(id, name), startPos(pos) {}
    
    Instant::Vector2 startPos;
    Instant::Vector2 playerPos;
    
    std::shared_ptr<Entity> player;
    
    void update() override {
        playerPos = player->getComponents<Transform>()[0]->position;
        
        if (playerPos.x < getComponents<Transform>()[0]->position.x)
            getComponents<CharacterBody>()[0]->velocity.x = -40;
        if (playerPos.x > getComponents<Transform>()[0]->position.x)
            getComponents<CharacterBody>()[0]->velocity.x = 40;
        if (playerPos.y < getComponents<Transform>()[0]->position.y)
            getComponents<CharacterBody>()[0]->velocity.y = -40;
        if (playerPos.y > getComponents<Transform>()[0]->position.y)
            getComponents<CharacterBody>()[0]->velocity.y = 40;
        
        if (getComponents<CollisionBox>()[0]->collidingWith.size() > 0) {
            for (std::weak_ptr<Entity> e : getComponents<CollisionBox>()[0]->collidingWith) {
                if (auto ent = e.lock()) {
                    auto player = std::dynamic_pointer_cast<Player>(ent);
                    if (player) {
                        // Reset player position
                        player->getComponents<Transform>()[0]->position = player->startPos;
                        getComponents<Transform>()[0]->position = startPos;
                    }
                }
            }
        }
    }

    void setup() override {
        // Add reference to player
        if (auto scene = m_scene.lock())
            player = scene->getEntityByName("Player");
        
        // CHANGE ENGINE GRAVITY
        Instant::gravity.y = 400;
        
        // Create components
        auto transform = std::make_shared<Transform>();
        transform->position = startPos;
        transform->scale = {1.0f, 1.0f};

        auto sprite = std::make_shared<Sprite>("player.png");
        
        auto collider = std::make_shared<CollisionBox>();
        collider->size = {64, 64};  // Example size
        collider->isPhysical = false;
        
        auto body = std::make_shared<CharacterBody>();

        // Add them to the entity instance
        addComponent(transform);
        addComponent(sprite);
        addComponent(collider);
        addComponent(body);

        // Can also run custom Enemy-specific logic here
        std::cout << "Enemy entity has been initialized.\n";
    }
};
