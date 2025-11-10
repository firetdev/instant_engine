// Base Entity class

#pragma once

#include "components/basecomponent.hpp"
#include "instant.hpp"

#include <vector>
#include <string>
#include <memory>

class Entity {
public:
    Entity(int id, std::string name) : id(id), name(name) {}

    template<typename T>
    void addComponent(std::shared_ptr<T> component);  // Add a component

    template<typename T>
    std::vector<std::shared_ptr<T>> getComponents();  // Return a vector linking to the components

private:
    int id;  // For identifying entities
    std::string name;  // Also for identification
    std::vector<std::shared_ptr<BaseComponent>> components;  // Vector of components
};

// Add a component
template<typename T>
void Entity::addComponent(std::shared_ptr<T> component) {
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
