#include "PirateShip.h"
#include <stdexcept>
#include <iostream>

PirateShip::PirateShip(float startX, float startY, float zigzagSpeed, float direction)
    : zigzagSpeed(zigzagSpeed), direction(direction), shootCooldown(2.0f), active(true) {
    if (!texture.loadFromFile("/Users/ammarmansa/Downloads/OOP last time/OOP last time/resources/pirate_ship.png")) {
        throw std::runtime_error("Failed to load pirate ship texture");
    }
    sprite.setTexture(texture);
    sprite.setScale(0.05f, 0.05f);
    sprite.setRotation(180.0f);
    sprite.setPosition(startX, startY);
}

void PirateShip::update() {
    float movement = zigzagSpeed * direction;
    sprite.move(movement, 2.0f); 
    if (sprite.getPosition().x <= 0 || sprite.getPosition().x + sprite.getGlobalBounds().width >= 800) {
        direction *= -1;
    }
}

void PirateShip::shoot(std::vector<Bullet>& bullets) {
    if (shootTimer.getElapsedTime().asSeconds() >= shootCooldown) {
        shootTimer.restart();
        float bulletX = sprite.getPosition().x + (sprite.getGlobalBounds().width / 2) - 2.5f;
        float bulletY = sprite.getPosition().y + sprite.getGlobalBounds().height;
        bullets.emplace_back(bulletX, bulletY, 0.0f, 5.0f);
        std::cout << "Pirate ship fired!" << std::endl;
    }
}

void PirateShip::draw(sf::RenderWindow& window) const {
    Entity::draw(window);
}

bool PirateShip::isActive() const {
    return active;
}

void PirateShip::setActive(bool isActive) {
    active = isActive;
}
