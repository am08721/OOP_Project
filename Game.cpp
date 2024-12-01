#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& window, sf::Font& font)
    : window(window), font(font), planetBase("Health and Ammo", 0),
      planetSpawnInterval(static_cast<float>(rand() % 20 + 10)),
      waveCount(1), waveInterval(10.0f), score(0),
      scoreText("Score: 0", font, 20), ammoText("", font, 20) {

    // setup background
    gameUniverse.generateBackground("/Users/ammarmansa/Downloads/OOP last time/OOP last time/resources/space_background.png", window);

    // setup score text
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    // setup ammo text
    ammoText.setFillColor(sf::Color::White);
    ammoText.setPosition(10, 40);
    ammoText.setString("Ammo: " + std::to_string(playerShip.getAmmo()));

    // health bar setup
    healthBarBack.setSize(sf::Vector2f(200.0f, 20.0f));
    healthBarBack.setFillColor(sf::Color(128, 128, 128));
    healthBarBack.setPosition(10.0f, 70.0f);

    healthBar.setSize(sf::Vector2f(200.0f, 20.0f));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(10.0f, 70.0f);
          
    if (!backgroundMusic.openFromFile("/Users/ammarmansa/Downloads/OOP last time/OOP last time/resources/mixkit-mystwrious-bass-pulse-2298.wav")) {
        std::cerr << "Failed to load background music!" << std::endl;
        exit(1);
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(50);
    backgroundMusic.play();

    if (!shootBuffer.loadFromFile("/Users/ammarmansa/Downloads/OOP last time/OOP last time/resources/mixkit-short-laser-gun-shot-1670.wav") ||
        !explosionBuffer.loadFromFile("/Users/ammarmansa/Downloads/OOP last time/OOP last time/resources/mixkit-falling-hit-757.wav") ||
        !collisionBuffer.loadFromFile("/Users/ammarmansa/Downloads/OOP last time/OOP last time/resources/mixkit-falling-hit-757.wav") ||
        !pickupBuffer.loadFromFile("/Users/ammarmansa/Downloads/OOP last time/OOP last time/resources/mixkit-space-coin-win-notification-271.wav")) {
        std::cerr << "Failed to load sound effects!" << std::endl;
        exit(1);
    }

    shootSound.setBuffer(shootBuffer);
    explosionSound.setBuffer(explosionBuffer);
    collisionSound.setBuffer(collisionBuffer);
    pickupSound.setBuffer(pickupBuffer);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // handle input
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                playerShip.shoot(playerBullets);
                shootSound.play();
            }
        }
    }

    // movement keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        playerShip.move(-1.0f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        playerShip.move(1.0f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        playerShip.move(0.0f, -1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        playerShip.move(0.0f, 1.0f);
    }
}

void Game::update() {
    ammoText.setString("Ammo: " + std::to_string(playerShip.getAmmo()));

    // spawn waves
    if (waveClock.getElapsedTime().asSeconds() >= waveInterval) {
        int shipsPerWave = rand() % 5 + 1;
        float gap = 800.0f / (shipsPerWave + 1);
        for (int i = 0; i < shipsPerWave; ++i) {
            float startX = gap * (i + 1) + static_cast<float>(rand() % 20 - 10);
            pirateShips.push_back(std::make_unique<PirateShip>(startX, -50.0f, 2.0f, 1.0f));
        }
        waveCount++;
        waveInterval *= 0.9f;
        waveClock.restart();
    }

    // spawn planet base
    if (!planetBase.isPlanetActive() && planetSpawnClock.getElapsedTime().asSeconds() >= planetSpawnInterval) {
        planetBase.spawn(static_cast<float>(rand() % static_cast<int>(window.getSize().x - 80) + 40), -50.0f);
        planetSpawnClock.restart();
        planetSpawnInterval = static_cast<float>(rand() % 20 + 10);
    }

    gameUniverse.update();
    playerShip.update();

    for (auto& pirate : pirateShips) {
        if (pirate->isActive()) {
            pirate->update();
            pirate->shoot(enemyBullets);
        }
    }

    planetBase.update();

    // check collisions
    for (auto& pirate : pirateShips) {
        if (pirate->isActive() && playerShip.getBounds().intersects(pirate->getBounds())) {
            playerShip.setHealth(playerShip.getHealth() - 20);
            pirate->setActive(false);
            collisionSound.play();
            if (playerShip.getHealth() <= 0 && !displayExitScreen()) {
                window.close();
                return;
            }
        }
    }

    if (planetBase.isPlanetActive() && planetBase.checkCollision(playerShip.getSprite())) {
        playerShip.setHealth(playerShip.getMaxHealth());
        playerShip.setAmmo(playerShip.getMaxAmmo());
        planetBase.deactivate();
        pickupSound.play();
    }

    // update bullets
    for (auto it = playerBullets.begin(); it != playerBullets.end();) {
        it->update();
        bool bulletRemoved = false;
        for (auto& pirate : pirateShips) {
            if (pirate->isActive() && it->getGlobalBounds().intersects(pirate->getBounds())) {
                pirate->setActive(false);
                explosionSound.play();
                it = playerBullets.erase(it);
                bulletRemoved = true;
                break;
            }
        }
        if (!bulletRemoved) {
            if (it->getPosition().y < 0) {
                it = playerBullets.erase(it);
            } else {
                ++it;
            }
        }
    }

    for (auto it = enemyBullets.begin(); it != enemyBullets.end();) {
        it->update();
        if (playerShip.getBounds().intersects(it->getGlobalBounds())) {
            playerShip.setHealth(playerShip.getHealth() - 10);
            collisionSound.play();
            it = enemyBullets.erase(it);
            if (playerShip.getHealth() <= 0 && !displayExitScreen()) {
                window.close();
                return;
            }
        } else if (it->getPosition().y > window.getSize().y) {
            it = enemyBullets.erase(it);
        } else {
            ++it;
        }
    }

    // update health bar
    float healthPercent = static_cast<float>(playerShip.getHealth()) / playerShip.getMaxHealth();
    healthBar.setSize(sf::Vector2f(200.0f * healthPercent, 20.0f));
    if (healthPercent > 0.6f) {
        healthBar.setFillColor(sf::Color::Green);
    } else if (healthPercent > 0.3f) {
        healthBar.setFillColor(sf::Color::Yellow);
    } else if (healthPercent > 0.2f) {
        healthBar.setFillColor(sf::Color::Red);
    } else {
        float flashTime = flashClock.getElapsedTime().asSeconds();
        healthBar.setFillColor(static_cast<int>(flashTime * 2) % 2 == 0 ? sf::Color::Red : sf::Color::Transparent);
    }
}

void Game::render() {
    window.clear();
    gameUniverse.draw(window);
    playerShip.draw(window);

    for (const auto& pirate : pirateShips) {
        if (pirate->isActive()) pirate->draw(window);
    }

    for (const auto& bullet : enemyBullets) bullet.draw(window);
    for (const auto& bullet : playerBullets) bullet.draw(window);

    planetBase.draw(window);
    window.draw(scoreText);
    window.draw(ammoText);
    window.draw(healthBarBack);
    window.draw(healthBar);

    window.display();
}

bool Game::displayExitScreen() {
    sf::Text gameOverText("Game Over", font, 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(window.getSize().x / 2.0f - gameOverText.getGlobalBounds().width / 2.0f, 100);

    sf::Text restartText("Press R to Restart or Esc to Exit", font, 24);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(window.getSize().x / 2.0f - restartText.getGlobalBounds().width / 2.0f, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) return true;
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return false;
                }
            }
        }

        window.clear();
        window.draw(gameOverText);
        window.draw(restartText);
        window.display();
    }

    return false;
}
