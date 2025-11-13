// GameManager implementation

#pragma once

#include "gamemanager.hpp"

void GameManager::changeScene(const std::string& sceneName) {
    auto it = m_sceneRegistry.find(sceneName);
    if (it == m_sceneRegistry.end()) {
        std::cerr << "Error: Scene not registered: " << sceneName << std::endl;
        return;
    }

    m_currentScene = it->second();
    m_currentScene->setup();
}

void GameManager::update() {
    // Check events
    inputSystem.update(m_window);
    
    // Update scenes
    if (m_currentScene) {
        m_currentScene->update();
    }
    m_window.clear(sf::Color::Black);
    m_currentScene->render(m_window);
    m_window.display();
}
