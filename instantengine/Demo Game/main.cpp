#include "engine/gamemanager.hpp"
#include "engine/entity.hpp"
#include "engine/components/transform.hpp"
#include "engine/components/sprite.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

int main() {
    // 1. Create the GameManager
    GameManager game(800, 600, "My Game Engine");
    sf::RenderWindow& window = game.getWindow();

    // 2. Create and add entities
    try {
        auto player = std::make_shared<Entity>(1, "Player");

        auto playerTransform = std::make_shared<Transform>();
        playerTransform->position = {400, 300}; // Center of the screen
        playerTransform->scale = {1, 1};

        // Make sure "player.png" exists!
        auto playerSprite = std::make_shared<Sprite>("player.png");
        
        player->addComponent(playerTransform);
        player->addComponent(playerSprite);
        game.addEntity(player);
    }
    catch (const std::exception& e) {
        // Handle texture loading failure
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    // 3. Run the main game loop
    while (window.isOpen()) {
        // 4a. Process window events
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
        }

        // 4b. Clear the window
        window.clear(sf::Color::Black); // Clear with a black background

        // 4c. Call game update (which calls RenderSystem::update)
        game.update();

        // 4d. Display the window
        window.display();
    }
    
    return 0;
}
