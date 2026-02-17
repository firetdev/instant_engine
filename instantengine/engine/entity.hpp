// Base Entity class

#pragma once

#include "components/basecomponent.hpp"

#include <vector>
#include <string>
#include <memory>

class Scene;  // Forward declaration

class Entity : public std::enable_shared_from_this<Entity> {
public:
    Entity(int id, std::string name) : id(id), name(name), type(name) {}

    template<typename T>
    void addComponent(std::shared_ptr<T> component);  // Add a component

    template<typename T>
    std::vector<std::shared_ptr<T>> getComponents();  // Return a vector linking to the components
    
    // Getters
    const std::string& getType() const { return type; }  // Return type
    const std::string& getName() const { return name; }  // Return name
    const int& getId() const { return id; }  // Return ID
    
    // Setters
    void setType(std::string newType) { type = newType; }  // Set type
    void setName(std::string newName) { name = newName; }  // Set name
    void setId(int newId) { id = newId; }  // Set ID
    void setScene(std::shared_ptr<Scene> sc) { m_scene = sc; }  // Set scene pointer
    
    virtual void update() = 0;  // Update function where entity logic will be coded
    virtual void setup() = 0;  // Setup function where components will be set up
protected:
    std::weak_ptr<Scene> m_scene;
    
private:
    int id;  // For identifying entities
    std::string name;  // Also for identification
    std::string type;  // Same as name, but can be shared by multiple entities
    std::vector<std::shared_ptr<BaseComponent>> components;  // Vector of components
};

// Add a component
template<typename T>
void Entity::addComponent(std::shared_ptr<T> component) {
    component->parent = shared_from_this();
    components.emplace_back(component);
}

// Return vector of components
template<typename T>
std::vector<std::shared_ptr<T>> Entity::getComponents() {
    std::vector<std::shared_ptr<T>> result;
    for (auto& comp : components) {
        if (auto casted = std::dynamic_pointer_cast<T>(comp))
            result.push_back(casted);
    }
    return result;
}
