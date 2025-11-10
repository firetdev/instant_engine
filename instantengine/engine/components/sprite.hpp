// Sprite struct

#pragma once

#include "../instant.hpp"
#include "basecomponent.hpp"

#include <SFML/Graphics.hpp>
#include <string>

struct Sprite : public BaseComponent {
    sf::Texture texture;  // Texture
    Instant::Vector2 position;  // Position relative to Entity's transform
    Instant::Vector2 scale;  // Scale, which will be multiplied by the Entity's transform's scale
    
    // Default constructor
    Sprite() = default;

    // Constructor that loads the texture from a file
    Sprite(const std::string& file, const Instant::Vector2& pos = {0, 0}, const Instant::Vector2& scl = {1, 1})
        : position(pos), scale(scl)
    {
        if (!texture.loadFromFile(file)) {
            throw std::runtime_error("Failed to load texture: " + file);
        }
    }
};
