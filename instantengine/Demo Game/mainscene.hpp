#pragma once

#include "../engine/engine.hpp"
#include "player.hpp"
#include "block.hpp"
#include "movingblock.hpp"
#include "enemy.hpp"

class MainScene : public Scene {
public:
    MainScene() : Scene("Main Scene") {}
    
    void setup() override {
        auto player = std::make_shared<Player>(1, "Player", Instant::Vector2(100, 100));
        addEntity(player);
        
        auto enemy = std::make_shared<Enemy>(1, "Enemy", Instant::Vector2(1000, 800));
        addEntity(enemy);
        
        auto moving = std::make_shared<MovingBlock>(1, "MovingBlock", Instant::Vector2(900, 400), 200, 150, 700);
        addEntity(moving);
        
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
