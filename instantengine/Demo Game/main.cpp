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
            getComponents<CharacterBody>()[0]->velocity.y = -1000 * Instant::delta;
        }
        if (Input::inputs["a"]) {
            getComponents<CharacterBody>()[0]->velocity.x = -100 * Instant::delta;
        }
        if (Input::inputs["d"]) {
            getComponents<CharacterBody>()[0]->velocity.x = 100 * Instant::delta;
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

class Enemy : public Entity {
public:
    Enemy(int id, const std::string& name)
            : Entity(id, name) {}
    
    void update() override {
        getComponents<CharacterBody>()[0]->velocity.x = 0;
        getComponents<CharacterBody>()[0]->velocity.y = 0;
        if (Input::inputs["Up"]) {
            getComponents<CharacterBody>()[0]->velocity.y = -100 * Instant::delta;
        }
        if (Input::inputs["Down"]) {
            getComponents<CharacterBody>()[0]->velocity.y = 100 * Instant::delta;
        }
        if (Input::inputs["Left"]) {
            getComponents<CharacterBody>()[0]->velocity.x = -100 * Instant::delta;
        }
        if (Input::inputs["Right"]) {
            getComponents<CharacterBody>()[0]->velocity.x = 100 * Instant::delta;
        }
    }

    void setup() override {
        // Create components
        auto transform = std::make_shared<Transform>();
        transform->position = {100, 200};
        transform->scale = {1.0f, 1.0f};

        auto sprite = std::make_shared<Sprite>("player.png");
        
        auto collider = std::make_shared<CollisionBox>();
        collider->size = {64, 64}; // Example size
        collider->isPhysical = true;

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
    GameManager game(800, 600, "My Game Engine");
    sf::RenderWindow& window = game.getWindow();

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

    while (window.isOpen()) {
        game.update();
    }
    
    return 0;
}
