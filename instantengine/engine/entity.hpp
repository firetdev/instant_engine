#pragma once

// Base Entity class

#include "components/basecomponent.hpp"

#include <vector>
#include <string>
#include <memory>

class Entity {
public:
    Entity(int id, std::string name) : id(id), name(name) {}

    template<typename T>
        void addComponent(std::shared_ptr<T> component); // <-- Changed

    template<typename T>
    std::vector<std::shared_ptr<T>> getComponents();

private:
    int id;
    std::string name;
    std::vector<std::shared_ptr<BaseComponent>> components;
};

// Add a component
template<typename T>
void Entity::addComponent(std::shared_ptr<T> component) { // <-- Changed
    components.push_back(component); // <-- Much simpler!
}

// Return vector of components
template<typename T>
std::vector<std::shared_ptr<T>> Entity::getComponents() {
    std::vector<std::shared_ptr<T>> result;
    for (auto& comp : components) {
        if (auto casted = std::dynamic_pointer_cast<T>(comp)) {
            result.push_back(casted);
        }
    }
    return result;
}
