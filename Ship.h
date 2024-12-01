#ifndef SHIP_H
#define SHIP_H

#include "Entity.h"
#include "Bullet.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Ship : public Entity {
public:
    Ship();

    void update() override;
    void draw(sf::RenderWindow& window) const override;

    void move(float dx, float dy);
    void shoot(std::vector<Bullet>& bullets);


    int getHealth() const;
    int getMaxHealth() const;
    int getPoints() const;
    int getAmmo() const;
    int getMaxAmmo() const;


    void setHealth(int h);
    void setPoints(int p);
    void setAmmo(int a);

    void increaseHealth(int amount);
    void increaseAmmo(int amount);
    void increasePoints(int amount);

    bool checkCollision(const sf::Sprite& other) const override;

private:
    int health;
    int maxHealth;
    int points;
    int ammo;
    int maxAmmo;
    float speed;
    sf::Texture texture;
};

#endif
