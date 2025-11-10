// Game manager class

#pragma once

#include "entity.hpp"
#include "components/sprite.hpp"
#include "systems/rendersystem.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

class GameManager {
public:
    // Constructor: sets up a non-resizable window
    GameManager(unsigned int width, unsigned int height, const std::string& title)
        : window(sf::VideoMode(sf::Vector2u(width, height)), title, sf::Style::Titlebar | sf::Style::Close) {}

    // Add an entity to the game
    void addEntity(std::shared_ptr<Entity> entity) {
        entities.push_back(entity);
    }
    
    // Update all systems
    void update() {
        renderer.update(entities, window);
    }

    // Accessors
    sf::RenderWindow& getWindow() { return window; }
    std::vector<std::shared_ptr<Entity>>& getEntities() { return entities; }

private:
    sf::RenderWindow window;
    std::vector<std::shared_ptr<Entity>> entities;
    RenderSystem renderer;
};
