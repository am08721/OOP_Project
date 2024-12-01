#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "screen.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "2D Space Shooter");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("/Users/ammarmansa/Downloads/OOP last time/OOP last time/resources/Arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    while (window.isOpen()) {
        
        StartScreen startScreen(window);
        bool startGame = startScreen.run();

        if (!startGame) {
            break;
        }

   
        Game game(window, font);
        game.run();
    }

    return 0;
}
