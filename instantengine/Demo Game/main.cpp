#include "../engine/engine.hpp"
#include "player.hpp"
#include "block.hpp"
#include "movingblock.hpp"

class MainScene : public Scene {
public:
    MainScene() : Scene("Main Scene") {}
    
    void setup() override {
        auto player = std::make_shared<Player>(1, "Player");
        addEntity(player);
        
        auto moving = std::make_shared<MovingBlock>(1, "Player", 200, 150, 700);
        addEntity(moving);
        moving->getComponents<Transform>()[0]->position = {900, 400};
        
        std::vector<std::shared_ptr<Block>> blocks;
        for (int i = 2; i <= 5; i++) {
            blocks.push_back(std::make_shared<Block>(i, "Block" + std::to_string(i)));
        }
        
        for(std::shared_ptr<Block> block : blocks) {
            addEntity(block);
        }
        
        blocks[0]->getComponents<Transform>()[0]->position = {100, 400};
        blocks[1]->getComponents<Transform>()[0]->position = {300, 300};
        blocks[2]->getComponents<Transform>()[0]->position = {700, 400};
        blocks[3]->getComponents<Transform>()[0]->position = {1100, 200};
        
        addLogicSystem(std::make_shared<CollisionSystem>());
        addLogicSystem(std::make_shared<PhysicsSystem>());
    }
};

int main() {
    GameManager game(1200, 800, "My Game Engine");
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
