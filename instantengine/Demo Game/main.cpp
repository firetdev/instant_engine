#include "mainscene.hpp"

int main() {
    GameManager game(1200, 800, "My Game Engine");
    sf::RenderWindow& window = game.getWindow();

    try {
        game.registerScene<MainScene>("Main");
        game.changeScene("Main");
        game.update();
    } catch (const std::exception& e) {
        // Handle texture loading failure
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    while (window.isOpen()) {
        game.update();
    }
    
    return 0;
}
