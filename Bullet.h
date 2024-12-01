#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
private:
    sf::CircleShape shape;
    float speedX;
    float speedY;
    bool active;

public:
    Bullet(float x, float y, float speedX, float speedY);

    void update();
    void draw(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    void deactivate();
    bool isActive() const;
};

#endif
