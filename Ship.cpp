#include "Ship.h"
#include <stdexcept>
#include <iostream>

Ship::Ship() : health(100), maxHealth(100), points(0), ammo(10), maxAmmo(10), speed(5.0f) {
    if (!texture.loadFromFile("/Users/ammarmansa/Downloads/OOP last time/OOP last time/resources/ship.png")) {
        throw std::runtime_error("Failed to load ship texture");
    }
    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);
    setPosition(400, 500);
}

void Ship::update() {
    // Check horizontal boundaries
    if (getPosition().x < 0) {
        setPosition(0, getPosition().y);
    } else if (getPosition().x + getBounds().width > 800) { 
        setPosition(800 - getBounds().width, getPosition().y);
    }

    // Check vertical boundaries
    if (getPosition().y < 0) {
        setPosition(getPosition().x, 0);
    } else if (getPosition().y + getBounds().height > 600) { 
        setPosition(getPosition().x, 600 - getBounds().height);
    }
}

void Ship::move(float dx, float dy) {
    
    sprite.move(dx * speed, dy * speed);

    
    if (sprite.getPosition().x < 0) {
        sprite.setPosition(0, sprite.getPosition().y);
    } else if (sprite.getPosition().x + sprite.getGlobalBounds().width > 800) {
        sprite.setPosition(800 - sprite.getGlobalBounds().width, sprite.getPosition().y);
    }
}


bool Ship::checkCollision(const sf::Sprite& other) const {
    return getBounds().intersects(other.getGlobalBounds());
}

void Ship::draw(sf::RenderWindow& window) const {
    Entity::draw(window); // Reuse base draw method
}



//! shoot method needs to show ammo count being decremented. 

void Ship::shoot(std::vector<Bullet>& bullets) {
    if (ammo > 0) {  
        ammo--;  
        float bulletX = getPosition().x + getBounds().width / 2 - 2.5;
        float bulletY = getPosition().y;  
        bullets.emplace_back(bulletX, bulletY, 0.0f, -5.0f); 
        std::cout << "Shooting bullet. Ammo left: " << ammo << std::endl;  
    } else {
        std::cout << "Out of ammo!" << std::endl;  
    }
}








int Ship::getHealth() const { return health; }
int Ship::getPoints() const { return points; }
int Ship::getAmmo() const { return ammo; }
int Ship::getMaxHealth() const { return maxHealth; }
int Ship::getMaxAmmo() const { return maxAmmo; }

void Ship::setHealth(int h) { health = h; }
void Ship::setPoints(int p) { points = p; }
void Ship::setAmmo(int a) { ammo = a; }

void Ship::increaseHealth(int amount) {
    health += amount;
    if (health > 100) health = 100;
    std::cout << "Health increased to: " << health << std::endl;
}

void Ship::increaseAmmo(int amount) {
    ammo += amount;
    std::cout << "Ammo refilled to: " << ammo << std::endl;
}

void Ship::increasePoints(int amount) {
    points += amount;
    std::cout << "Points increased to: " << points << std::endl;
}



