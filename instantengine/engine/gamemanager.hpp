// GameManager class

#pragma once

#include "scene.hpp"

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <map>
#include <functional>

class GameManager {
public:
    GameManager(unsigned int width, unsigned int height, const std::string& title)
        : m_window(sf::VideoMode(sf::Vector2u(width, height)), title, sf::Style::Titlebar | sf::Style::Close) {}
    
    void update();  // Update and render

    // The new way to change scenes
    void changeScene(const std::string& sceneName);

    // Register a scene
    template<typename T>
    void registerScene(const std::string& sceneName) {
        m_sceneRegistry[sceneName] = []() {
            return std::make_shared<T>();
        };
    }

    sf::RenderWindow& getWindow() { return m_window; }

private:
    sf::RenderWindow m_window;
    
    std::shared_ptr<Scene> m_currentScene;     // The current scene
    // The registry that knows how to create all other scenes
    std::map<std::string, std::function<std::shared_ptr<Scene>()>> m_sceneRegistry;
};
