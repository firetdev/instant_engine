#include "../engine/engine.hpp"

class Player : public Entity {
public:
    Player(int id, const std::string& name)
            : Entity(id, name) {}
    
    void update() override {
        getComponents<CharacterBody>()[0]->velocity.x = 0;
        getComponents<CharacterBody>()[0]->velocity.y = 0;
        if (Input::inputs["w"]) {
            getComponents<CharacterBody>()[0]->velocity.y = -100 * Instant::delta;
        }
        if (Input::inputs["s"]) {
            getComponents<CharacterBody>()[0]->velocity.y = 100 * Instant::delta;
        }
        if (Input::inputs["a"]) {
            getComponents<CharacterBody>()[0]->velocity.x = -100 * Instant::delta;
        }
        if (Input::inputs["d"]) {
            getComponents<CharacterBody>()[0]->velocity.x = 100 * Instant::delta;
        }
        
        for (auto& e : getComponents<CollisionBox>()[0]->collidingWith) {
            if (e.lock()->getName() == "Enemy")
                std::cout << "Colliding with enemy!\n";
        }
    }

    void setup() override {
        // Create components
        auto transform = std::make_shared<Transform>();
        transform->position = {100, 100};
        transform->scale = {1.0f, 1.0f};

        auto sprite = std::make_shared<Sprite>("player.png");
        
        auto collider = std::make_shared<CollisionBox>();
        collider->size = {64, 64}; // Example size
        collider->isPhysical = false;
        
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

class Enemy : public Entity {
public:
    Enemy(int id, const std::string& name)
            : Entity(id, name) {}
    
    void update() override {
        getComponents<CharacterBody>()[0]->velocity.x = 0;
        getComponents<CharacterBody>()[0]->velocity.y = 0;
        if (Input::inputs["w"]) {
            getComponents<CharacterBody>()[0]->velocity.y = 100 * Instant::delta;
        }
        if (Input::inputs["s"]) {
            getComponents<CharacterBody>()[0]->velocity.y = -100 * Instant::delta;
        }
        if (Input::inputs["a"]) {
            getComponents<CharacterBody>()[0]->velocity.x = 100 * Instant::delta;
        }
        if (Input::inputs["d"]) {
            getComponents<CharacterBody>()[0]->velocity.x = -100 * Instant::delta;
        }
    }

    void setup() override {
        // Create components
        auto transform = std::make_shared<Transform>();
        transform->position = {200, 200};
        transform->scale = {1.0f, 1.0f};

        auto sprite = std::make_shared<Sprite>("player.png");
        
        auto collider = std::make_shared<CollisionBox>();
        collider->size = {64, 64}; // Example size
        collider->isPhysical = false;

        auto body = std::make_shared<CharacterBody>();
        
        // Add them to the entity instance
        addComponent(transform);
        addComponent(sprite);
        addComponent(collider);
        addComponent(body);

        // Can also run custom Player-specific logic here
        std::cout << "Enemy entity has been initialized.\n";
    }
};

class MainScene : public Scene {
public:
    MainScene() : Scene("Main Scene") {}
    
    void setup() override {
        auto player = std::make_shared<Player>(1, "Player");
        addEntity(player);
        auto enemy = std::make_shared<Enemy>(1, "Enemy");
        addEntity(enemy);
        addLogicSystem(std::make_shared<CollisionSystem>());
        addLogicSystem(std::make_shared<PhysicsSystem>());
    }
};

int main() {
    // 1. Create the GameManager
    GameManager game(800, 600, "My Game Engine");
    sf::RenderWindow& window = game.getWindow();

    // 2. Create and add entities
    try {
        game.registerScene<MainScene>("Main");
        game.changeScene("Main");
        game.update();
    }
    catch (const std::exception& e) {
        // Handle texture loading failure
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    // 3. Run the main game loop
    while (window.isOpen()) {
        // 4a. Process window events
        /*while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
        }*/

        // 4b. Clear the window
        //window.clear(sf::Color::Black); // Clear with a black background

        // 4c. Call game update (which calls RenderSystem::update)
        game.update();

        // 4d. Display the window
        //window.display();
    }
    
    return 0;
}
