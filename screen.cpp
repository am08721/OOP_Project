#include "screen.h"
#include <iostream>

StartScreen::StartScreen(sf::RenderWindow& window)
    : window(window) {

    //  custom font
    if (!font.loadFromFile("/Users/ammarmansa/Downloads/OOP last time/OOP last time/resources/Orbitron-Regular.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    // title text
    titleText.setFont(font);
    titleText.setString("Space Shooter");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(
        window.getSize().x / 2.0f - titleText.getGlobalBounds().width / 2.0f,
        window.getSize().y / 2.0f - 100
    );

    // play text
    playText.setFont(font);
    playText.setString("Press Enter to Play");
    playText.setCharacterSize(30);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(
        window.getSize().x / 2.0f - playText.getGlobalBounds().width / 2.0f,
        window.getSize().y / 2.0f + 50
    );
}

bool StartScreen::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    return true;
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return false;
                }
            }
        }
        float elapsed = animationClock.getElapsedTime().asSeconds();

        float scale = 1.0f + 0.1f * std::sin(elapsed * 2.0f); 
        titleText.setScale(scale, scale);

        sf::Uint8 red = static_cast<sf::Uint8>(128 + 127 * std::sin(elapsed * 2.0f));
        sf::Uint8 green = static_cast<sf::Uint8>(128 + 127 * std::sin(elapsed * 2.0f + 2));
        sf::Uint8 blue = static_cast<sf::Uint8>(128 + 127 * std::sin(elapsed * 2.0f + 4));
        titleText.setFillColor(sf::Color(red, green, blue));

        window.clear();
        window.draw(titleText);
        window.draw(playText);
        window.display();
    }
    return false;
}
