// RenderSystem class

#pragma once

#include "../entity.hpp"
#include "../components/sprite.hpp"
#include "../components/transform.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class RenderSystem {
public:
    // Update function: render all entities with both Transform and Sprite
    void update(const std::vector<std::shared_ptr<Entity>>& entities, sf::RenderWindow& window) {
        for (auto& entity : entities) {
            // Get the first Transform and Sprite component (assumes one of each)
            auto transformComponents = entity->getComponents<Transform>();
            auto spriteComponents = entity->getComponents<Sprite>();

            if (transformComponents.empty() || spriteComponents.empty())
                continue; // Skip entities without both components

            auto transform = transformComponents[0];
            // Loop through all Sprite components
            for (auto& spriteData : spriteComponents) {
                sf::Sprite sprite(spriteData->texture);
                sprite.setTexture(spriteData->texture);

                // Set position: entity transform + sprite relative position
                sprite.setPosition(sf::Vector2f(transform->position.x + spriteData->position.x,
                                   transform->position.y + spriteData->position.y));

                // Set scale: entity transform scale * sprite relative scale
                sprite.setScale(sf::Vector2f(transform->scale.x * spriteData->scale.x,
                                transform->scale.y * spriteData->scale.y));

                // Draw to the window
                window.draw(sprite);
            }
        }
    }
};
