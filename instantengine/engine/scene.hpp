// Scene class

#pragma once

#include "entity.hpp"
#include "basesystem.hpp"
#include "rendersystem.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

class Scene {
public:
    // Constructor: sets up a non-resizable window
    Scene(const std::string name)
        : m_name(name) {}

    virtual ~Scene() = default;
    
    // Add an entity to the game
    void addEntity(std::shared_ptr<Entity> entity) {
        entity->setup();
        
        // Make sure there are no repeated ids or names
        int newId = entity->getId();
        for (auto& e : m_entities)
            newId = std::max(newId, e->getId() + 1);

        entity->setId(newId);
        
        std::string baseName = entity->getName();
        int nameNumber = 0;
        
        bool restart = true;
        while (restart) {
            restart = false;
            std::string candidate = (nameNumber == 0 ? baseName : baseName + std::to_string(nameNumber));

            for (auto& e : m_entities) {
                if (candidate == e->getName()) {
                    nameNumber++;
                    restart = true;
                    break;
                }
            }

            if (!restart)
                entity->setName(candidate);
        }
        
        m_entities.push_back(entity);
    }
    
    // Update all systems
    void update() {
        for (auto& entity : m_entities) {
            entity->update();
        }
        for (auto& system : m_logicSystems) {
            system->update(m_entities); // Pass the entities
        }
        
        onUpdate();  // Call custom scene logic
    }
    
    void render(sf::RenderWindow& window) {
        m_renderSystem->update(m_entities, window);
    }

    virtual void setup() = 0;  // Set up scene. Required so that scenes reset when reloaded
    
    // Accessors
    std::vector<std::shared_ptr<Entity>>& getEntities() { return m_entities; }
    const std::string& getName() const { return m_name; }

protected:
    virtual void onUpdate() {}  // Override to run custom scene update code
    
    // Add a logic system (Collision, Physics, Input)
    void addLogicSystem(std::shared_ptr<BaseSystem> system) {
        m_logicSystems.push_back(system);
    }
    
    // Set the render system
    void setRenderSystem(std::shared_ptr<RenderSystem> system) {
        m_renderSystem = system;
    }
    
private:
    std::string m_name;
    std::vector<std::shared_ptr<Entity>> m_entities;
    std::vector<std::shared_ptr<BaseSystem>> m_logicSystems;
    std::shared_ptr<RenderSystem> m_renderSystem;
};
