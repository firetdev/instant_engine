#include "../engine/engine.hpp"

class Player : public Entity {
public:
    Player(int id, const std::string& name)
            : Entity(id, name) {}
    
    void update() override {
        std::cout << "yo";
    }

    void setup() override {
        // Create components
        auto transform = std::make_shared<Transform>();
        transform->position = {100, 100};
        transform->scale = {1.0f, 1.0f};

        auto sprite = std::make_shared<Sprite>("player.png");
        
        auto collider = std::make_shared<CollisionBox>();
        collider->size = {32, 32}; // Example size
        collider->isPhysical = true;

        // Add them to the entity instance
        addComponent(transform);
        addComponent(sprite);
        addComponent(collider);

        // Can also run custom Player-specific logic here
        std::cout << "Player entity has been initialized.\n";
    }
};

int main() {
    // 1. Create the GameManager
    GameManager game(800, 600, "My Game Engine");
    sf::RenderWindow& window = game.getWindow();

    // 2. Create and add entities
    try {
        auto player = std::make_shared<Player>(1, "Player");
        player->setup();
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
