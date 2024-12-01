#ifndef PIRATESHIP_H
#define PIRATESHIP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"
#include "Entity.h"

class PirateShip : public Entity {
private:
    sf::Texture texture;
    float shootCooldown;
    sf::Clock shootTimer;
    float zigzagSpeed;
    float direction;
    bool active; 

public:
    PirateShip(float startX, float startY, float zigzagSpeed, float direction);

    void update() override;  
    void shoot(std::vector<Bullet>& bullets);
    void draw(sf::RenderWindow& window) const override;
    bool isActive() const;
    void setActive(bool isActive);
};

#endif
