#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <SFML/Graphics.hpp>

class StartScreen {
public:
    StartScreen(sf::RenderWindow& window);
    bool run();

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text titleText;
    sf::Text playText;
    sf::Clock animationClock;
};

#endif 