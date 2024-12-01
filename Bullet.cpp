#include "Bullet.h"

Bullet::Bullet(float x, float y, float speedX, float speedY)
    : speedX(speedX), speedY(speedY), active(true) {
    shape.setRadius(5.0f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
}

void Bullet::update() {
    if (active) {
        shape.move(speedX, speedY);
        if (shape.getPosition().x < 0 || shape.getPosition().x > 800 ||
            shape.getPosition().y < 0 || shape.getPosition().y > 600) {
            active = false;
        }
    }
}

void Bullet::draw(sf::RenderWindow& window) const {
    if (active) {
        window.draw(shape);
    }
}

sf::Vector2f Bullet::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Bullet::getGlobalBounds() const {
    return shape.getGlobalBounds();
}

void Bullet::deactivate() {
    active = false;
}

bool Bullet::isActive() const {
    return active;
}
