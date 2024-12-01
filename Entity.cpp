#include "Entity.h"

void Entity::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Entity::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition();
}

void Entity::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

bool Entity::checkCollision(const sf::Sprite& other) const {
    return sprite.getGlobalBounds().intersects(other.getGlobalBounds());
}

const sf::Sprite& Entity::getSprite() const {
    return sprite;
}
