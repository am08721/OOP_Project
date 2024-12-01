#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Universe.h"
#include "Ship.h"
#include "PirateShip.h"
#include "Bullet.h"
#include "PlanetBase.h"

class Game {
public:
    Game(sf::RenderWindow& window, sf::Font& font);
    void run();
    

    // Declare sound buffers and sounds
    sf::Music backgroundMusic;
    sf::SoundBuffer shootBuffer;
    sf::SoundBuffer explosionBuffer;
    sf::SoundBuffer collisionBuffer;
    sf::SoundBuffer pickupBuffer;

    sf::Sound shootSound;
    sf::Sound explosionSound;
    sf::Sound collisionSound;
    sf::Sound pickupSound;


private:
    // Member functions
    void processEvents();
    void update();
    void render();
    bool displayExitScreen();
    
    // Member variables
    sf::RenderWindow& window;
    sf::Font& font;

    Universe gameUniverse;
    Ship playerShip;
    PlanetBase planetBase;

    sf::Clock planetSpawnClock;
    float planetSpawnInterval;

    std::vector<std::unique_ptr<PirateShip>> pirateShips;
    std::vector<Bullet> enemyBullets;
    std::vector<Bullet> playerBullets;
    sf::Clock waveClock;
    int waveCount;
    float waveInterval;

    int score;
    sf::Text scoreText;
    sf::Text ammoText;
    sf::Clock scoreClock;

    sf::RectangleShape healthBarBack;
    sf::RectangleShape healthBar;
    sf::Clock flashClock;
};

#endif 
