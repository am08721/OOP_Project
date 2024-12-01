#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual ~Entity() = default;

    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) const;
    virtual sf::FloatRect getBounds() const;
    virtual sf::Vector2f getPosition() const;
    virtual void setPosition(float x, float y);

    virtual bool checkCollision(const sf::Sprite& other) const;
    virtual const sf::Sprite& getSprite() const;

protected:
    sf::Sprite sprite;
};

#endif