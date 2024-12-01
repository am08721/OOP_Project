#include "PlanetBase.h"
#include <iostream>


PlanetBase::PlanetBase(const std::string& resource, int price)
    : tradeResource(resource), tradePrice(price), isActive(false) {
    if (!texture.loadFromFile("/Users/ammarmansa/Downloads/OOP last time/OOP last time/resources/planet.png")) {
        std::cerr << "Failed to load planet texture!" << std::endl;
        isActive = false;
    } else {
        sprite.setTexture(texture);
        sprite.setScale(0.1f, 0.1f);  
        sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    }
}


void PlanetBase::spawn(float x, float y) {
    sprite.setPosition(x,y);
    isActive = true;  
}


void PlanetBase::deactivate() {
    isActive = false;
}


bool PlanetBase::checkCollision(const sf::Sprite& shipSprite) const {
    if (!isActive) return false;

    return sprite.getGlobalBounds().intersects(shipSprite.getGlobalBounds());
}



void PlanetBase::draw(sf::RenderWindow& window) {
    if (isActive) {
        window.draw(sprite);
    }
}


bool PlanetBase::isPlanetActive() const {
    return isActive;
}

void PlanetBase::update() {
    if (isActive) {
        sprite.move(0.0f, 1.0f);  
        if (sprite.getPosition().y > 600.0f) {
            isActive = false;
        }
    }
}
