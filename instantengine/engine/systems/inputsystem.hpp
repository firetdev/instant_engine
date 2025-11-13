// InputSystem class

#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

// Input system is NOT a BaseSystem, because it is managed by the GameManager
class InputSystem {
public:
    // Check events
    void update(sf::RenderWindow& window) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }
};

