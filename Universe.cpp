#include "Universe.h"
#include <cstdlib>
#include <ctime>
using namespace std;

Universe::Universe() : scrollSpeed(2.0f) {
    srand(time(nullptr));
}

void Universe::generateBackground(const std::string& backgroundImagePath, const sf::RenderWindow& window) {
    if (!backgroundTexture.loadFromFile("/Users/ammarmansa/Downloads/OOP last time/OOP last time/resources/space_background.png")) {
        throw std::runtime_error("Failed to load background image");
    }

    backgroundSprite1.setTexture(backgroundTexture);
    backgroundSprite2.setTexture(backgroundTexture);

    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;

    backgroundSprite1.setScale(scaleX, scaleY);
    backgroundSprite2.setScale(scaleX, scaleY);

    backgroundSprite1.setPosition(0, 0);
    backgroundSprite2.setPosition(0, -backgroundTexture.getSize().y * scaleY);
}

void Universe::update() {
    backgroundSprite1.move(0, scrollSpeed);
    backgroundSprite2.move(0, scrollSpeed);

    if (backgroundSprite1.getPosition().y >= backgroundTexture.getSize().y * backgroundSprite1.getScale().y) {
        backgroundSprite1.setPosition(0, backgroundSprite2.getPosition().y - backgroundTexture.getSize().y * backgroundSprite2.getScale().y);
    }

    if (backgroundSprite2.getPosition().y >= backgroundTexture.getSize().y * backgroundSprite2.getScale().y) {
        backgroundSprite2.setPosition(0, backgroundSprite1.getPosition().y - backgroundTexture.getSize().y * backgroundSprite1.getScale().y);
    }
}

void Universe::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite1);
    window.draw(backgroundSprite2);
}
