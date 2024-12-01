#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include <string>

class Universe {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite1;
    sf::Sprite backgroundSprite2;
    float scrollSpeed;

public:
    Universe();

    void generateBackground(const std::string& backgroundImagePath, const sf::RenderWindow& window);
    void update();
    void draw(sf::RenderWindow& window);
};

#endif // UNIVERSE_H
