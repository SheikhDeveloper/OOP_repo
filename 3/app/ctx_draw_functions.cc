#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "grid.h"
#include "cloud.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

int main() {

    srand(static_cast<unsigned int>(time(nullptr))); // Seed for random number generation
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Ocean and Sky Scene");
    window.setFramerateLimit(60);

    // Create the sky
    sf::RectangleShape sky(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2));
    sky.setFillColor(sf::Color(135, 206, 235)); // Light blue color for the sky

    // Create the ocean
    sf::RectangleShape ocean(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2));
    ocean.setPosition(0, SCREEN_HEIGHT / 2);
    ocean.setFillColor(sf::Color(0, 0, 255));

    sf::Texture aircraftCarrierTexture;
    if (!aircraftCarrierTexture.loadFromFile("/home/sheikh/oop2024/3/app/images/aircraft_carrier.png")) {
        throw std::runtime_error("Failed to load aircraft carrier texture");
    }
    sf::Texture aircraftCruiserTexture;
    if (!aircraftCruiserTexture.loadFromFile("/home/sheikh/oop2024/3/app/images/aircraft_cruiser.png")) {
        throw std::runtime_error("Failed to load aircraft cruiser texture");
    }
    sf::Texture coveringShipTexture;
    if (!coveringShipTexture.loadFromFile("/home/sheikh/oop2024/3/app/images/covering_ship.png")) {
        throw std::runtime_error("Failed to load covering ship texture");
    }

    // Create the aircraft
    sf::Sprite aircraftCarrierSprite(aircraftCarrierTexture);
    aircraftCarrierSprite.setScale(0.25f, 0.2f);
    aircraftCarrierSprite.setPosition(50 + aircraftCarrierSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - aircraftCarrierSprite.getGlobalBounds().height / 2);
    sf::Sprite aircraftCruiserSprite(aircraftCruiserTexture);
    aircraftCruiserSprite.setScale(0.25f, 0.25f);
    aircraftCruiserSprite.setPosition(50 + aircraftCruiserSprite.getGlobalBounds().width / 2 + aircraftCarrierSprite.getGlobalBounds().width + 50, SCREEN_HEIGHT / 2 - aircraftCruiserSprite.getGlobalBounds().height / 2);
    sf::Sprite coveringShipSprite(coveringShipTexture);
    coveringShipSprite.setScale(0.25f, 0.25f);
    coveringShipSprite.setPosition(SCREEN_WIDTH / 2 - coveringShipSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - coveringShipSprite.getGlobalBounds().height / 2 + aircraftCruiserSprite.getGlobalBounds().height);

/*    Grid grid(SCREEN_WIDTH, SCREEN_HEIGHT, 300, 100);
    grid.addCell(aircraftCarrierSprite);
    grid.addCell(aircraftCruiserSprite);
    grid.addCell(coveringShipSprite); */

    const float cloudWidth = 50;
    const float cloudHeight = 25;
    sf::Texture cloudTexture;
    if (!cloudTexture.loadFromFile("/home/sheikh/oop2024/3/app/images/cloud.png")) {
        throw std::runtime_error("Failed to load cloud texture");
    }

    std::vector<Cloud> clouds;

    for (int i = 0; i < 20; ++i) {
        float x = rand() % SCREEN_WIDTH + SCREEN_WIDTH; // Start off-screen to the right
        float y = rand() % 200 + 50; // Random vertical position
        clouds.emplace_back(cloudTexture, x, y);
    }

     float cloudSpeed = 2.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (auto& cloud : clouds) {
            cloud.update(cloudSpeed);
        }

        // Clear the window
        window.clear();

        // Draw the sky and ocean
        window.draw(sky);
        window.draw(ocean);

        // Draw the ships
        window.draw(aircraftCarrierSprite);
        window.draw(aircraftCruiserSprite);
        window.draw(coveringShipSprite);

        for (auto& cloud : clouds) {
            cloud.draw(window);
        }

        // Display the contents of the window
        window.display();
    }

    return 0;
}
