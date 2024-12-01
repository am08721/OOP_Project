#ifndef PLANETBASE_H
#define PLANETBASE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;

class PlanetBase {
private:
    
    sf::Texture texture;
    sf::Sprite sprite;
    string tradeResource;
    int tradePrice;
    bool isActive;

    
    
public:
    PlanetBase(const string& resource, int price);

    void update();
    
    void spawn(float x,float y);
    void deactivate();
    bool checkCollision(const sf::Sprite& shipSprite) const;
    
    
    void draw(sf::RenderWindow& window);
    
    bool isPlanetActive() const;
    
};
#endif
